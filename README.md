# A dependency-free C++ HOCON Parser

This is a port of the TypesafeConfig library to C++.

It is a modified version of the puppetlabs original, using the bazel build system
and with dependencies on Leatherman and Boost removed.

The library provides C++ support for the [HOCON configuration file format](https://github.com/typesafehub/config/blob/master/HOCON.md).

```
          MMMMMMMMMMMMMMMMMMMM
         .====================.
         MMMMMMMMMMMMMMMMMMMMMM
        .MMMMMMMMMMMMMMMMMMMMMM.
    ===.7MMMIN7NMMMMMMMMM7M=MMMM,===
    MMM.7MM:     DMMMMM7    :MMM=MMM
    MMM.7MM,     DMMMMM?    ~MMM=MMM
    MMM.7MMM~++~?MMMMMMM~++~MMMM=MMM
        .MMMMMMMMMMMMMMMMMMMMMM.
         MMMMMMMMMMMMMMMMMMMMMM
         MMMMMMMMMMMMMMMMMMMMMM
         MMM      HOCON     MMM
         MMMMMMMMMMMMMMMMMMMMMM
          .MMMMMMMMMMMMMMMMMM.
          .MMMMMMMMMMMMMMMMMM.
       .MMMMMMMMMMMMMMMMMMMMMMMM
 .    MMMMMMMMMMMMM88MMMMMMMMMM8MM    .
7=MMMMMMMM++ A CONFIG FILE  ++M8MMMMMM7=
M=MMMMMMMM+ FORMAT DESIGNED  +M8MMMMMM7M
M=MMMMMMMM++  FOR HUMANS   ++M8MMMMMM7M
 =MMMMMMMMMMMMMMMMM88MMMMMMMMMM8MMMMMM7
  7MM.88MMMMMMMMMMM88MMMMMMMMMMO88 MM8
  7MM   MMMMMMMMMMM88MMMMMMMMMM8   MM8
  7MM   MMMMMMMMMMM88MMMMMMMMMM8   MM8
  7MM   MMMDMMMM?MM88MM?MMMMOMM8   MM8
```
