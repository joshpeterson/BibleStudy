BibleStudy
==========
BibleStudy is a C++/Qt bible searching and browsing application which runs on Windows and Linux.

Dependencies
------------
* Qt 4.4.0
* Google Protocol Buffers 2.2.0
* Boost 1.40 (headers, filesystem library and system library)
* CPPUnit 1.12.1 (for unit tests)

Build Environment
-----------------
* Windows: Visual Studio 2008
* Linux: g++ 4.4.3

Qt Build Options
----------------

To ease distribution, BibleStudy is statically linked to Qt and the C++ runtime.

In the Qt Windows build, the following changes were made to the mkspecs\win32-msvc2008 file:

* QMAKE_CFLAGS_RELEASE = -O2 -GL -arch:SSE -MT -MD
* QMAKE_LFLAGS_RELEASE = /INCREMENTAL:NO /NODEFAULTLIB:"MSVCRT" /LTCG

The following configure command was used:

* configure -release -no-libjpeg -qt-zlib -qt-libpng -no-exceptions -no-stl -no-rtti -no-qt3support -no-openssl -no-opengl -no-webkit -no-phonon -no-style-motif -no-style-cde -no-style-cleanlooks -no-style-plastique -no-sql-sqlite -mmx -static -platform win32-msvc2008

Branching Model
---------------
The BibleStudy branching model is based on [this one](http://nvie.com/posts/a-successful-git-branching-model/).

* Branch master is the release branch
* Branch develop is the current development branch
* Features are branched from the develop branch and merged back in when they are complete

For Example:

To create a branch for a new feature:

`git checkout -b myfeature develop`

To merge that feature back into the development branch:

`git checkout develop`

`git merge --no-ff myfeature`

`git branch -d myfeature`

`git push origin :myfeature` (if the feature branch was pushed to github)

`git push origin develop`
