{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.ccls

    pkgs.valgrind

    # keep this line if you use bash
    pkgs.bashInteractive
  ];
}
