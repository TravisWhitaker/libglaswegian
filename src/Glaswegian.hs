module Glaswegian where

import Control.Monad.Primitive

import Data.Coerce

import qualified Data.IntMap.Strict as IM

import Data.IORef

import Data.Primitive.ByteArray

import Foreign.C.Types
import Foreign.Ptr
import Foreign.StablePtr

import System.IO.Unsafe

type IOMBA = MutableByteArray RealWorld

type VoidStar = Ptr ()

stabTab :: IORef (IM.IntMap (StablePtr IOMBA))
stabTab = unsafePerformIO (newIORef IM.empty)

ghc_alloc :: CSize -> IO VoidStar
ghc_alloc s = do
    mba <- newPinnedByteArray (fromIntegral s)
    sp <- newStablePtr mba
    let mbac = castPtr (mutableByteArrayContents mba)
        ip   = coerce (ptrToIntPtr mbac)
    atomicModifyIORef' stabTab (\t -> (IM.insert ip sp t,()))
    pure mbac

foreign export ccall ghc_alloc :: CSize -> IO VoidStar

-- ghc_realloc ::

ghc_free :: VoidStar -> IO ()
ghc_free mbac = do
    let ip = coerce (ptrToIntPtr mbac)
        f t =
            let (Just sp, t') = IM.updateLookupWithKey (\_ _ -> Nothing) ip t
            in (t', sp)
    sp <- atomicModifyIORef' stabTab f
    freeStablePtr sp

foreign export ccall ghc_free :: VoidStar -> IO ()
