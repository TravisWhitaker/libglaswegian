let pinned-nixpkgs = builtins.fetchGit
    {
        url = "https://github.com/nixos/nixpkgs";
        ref = "master";
        rev = "1fe82110febdf005d97b2927610ee854a38a8f26";
    };
in with import pinned-nixpkgs {};
runCommand "libglaswegian-env"
{
    buildInputs =
        let thisghc = haskell.packages.ghc882.ghcWithPackages
            (p: [ p.cabal-install
                  p.ghci
                ]);
        in [ binutils
             thisghc
           ];
} ""
