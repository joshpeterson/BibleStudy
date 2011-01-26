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

Building
-------
* Linux: From the root BibleStudy directory, run the build/linux/build.sh script
* Windows: From the root BibleStudy directory, run the build\win\Build.bat script

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

To create a release:

`git checkout -b release-1.2 develop`

`update version`

`git commit -a -m "Bumped version number to 1.2"`

`Build product and installer`

`git checkout master`

`git merge --no-ff release-1.2`

`git tag -a 1.2`

`git checkout develop`

`git merge --no-ff release-1.2`

`git branch -d release-1.2`

`git push origin :release-1.2` (if the release branch was pushed to github)
