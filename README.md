```shell
$ git clone git clone https://github.com/LiWinDom/lab08
```
```shell
Cloning into 'lab08'...
remote: Enumerating objects: 76, done.
remote: Counting objects: 100% (3/3), done.
remote: Compressing objects: 100% (3/3), done.
remote: Total 76 (delta 0), reused 0 (delta 0), pack-reused 73
Receiving objects: 100% (76/76), 951.66 KiB | 2.97 MiB/s, done.
Resolving deltas: 100% (22/22), done.
```

```shell
$ cd lab08/
```

```shell
$ cp -r ../lab05/banking/ ./banking/
```

```
$ touch Dockerfile
```

```shell
$ brew install --cask docker
```
```shell
==> Downloading https://raw.githubusercontent.com/Homebrew/homebrew-cask/f65ed0299d1f5d133b539dba798fe18f49b2c6fb/Casks/d/docker.rb
Already downloaded: /Users/LiWinDom/Library/Caches/Homebrew/downloads/8f1296f850c2722317b77e85949809ad8d6a631abba92087cac6e810fbe61caf--docker.rb
==> Downloading https://desktop.docker.com/mac/main/amd64/149282/Docker.dmg
########################################################################################################################################################################################################## 100.0%
==> Installing Cask docker
==> Moving App 'Docker.app' to '/Applications/Docker.app'
==> Linking Binary 'docker-compose.zsh-completion' to '/usr/local/share/zsh/site-functions/_docker-compose'
==> Linking Binary 'docker-compose.fish-completion' to '/usr/local/share/fish/vendor_completions.d/docker-compose.fish'
==> Linking Binary 'com.docker.cli' to '/usr/local/bin/com.docker.cli'
==> Linking Binary 'docker' to '/usr/local/bin/docker'
==> Linking Binary 'docker-compose' to '/usr/local/bin/docker-compose'
==> Linking Binary 'docker-credential-desktop' to '/usr/local/bin/docker-credential-desktop'
==> Linking Binary 'docker-credential-ecr-login' to '/usr/local/bin/docker-credential-ecr-login'
==> Linking Binary 'docker-credential-osxkeychain' to '/usr/local/bin/docker-credential-osxkeychain'
==> Linking Binary 'docker-index' to '/usr/local/bin/docker-index'
==> Linking Binary 'hub-tool' to '/usr/local/bin/hub-tool'
==> Linking Binary 'kubectl' to '/usr/local/bin/kubectl.docker'
==> Linking Binary 'docker.bash-completion' to '/usr/local/etc/bash_completion.d/docker'
==> Linking Binary 'docker.zsh-completion' to '/usr/local/share/zsh/site-functions/_docker'
==> Linking Binary 'docker.fish-completion' to '/usr/local/share/fish/vendor_completions.d/docker.fish'
==> Linking Binary 'com.docker.hyperkit' to '/usr/local/bin/hyperkit'
==> Linking Binary 'docker-compose.bash-completion' to '/usr/local/etc/bash_completion.d/docker-compose'
🍺  docker was successfully installed!
```

```shell
$ docker build ./ -t banking
```
```shell
[+] Building 0.8s (12/12) FINISHED                                                                   docker:desktop-linux
 => [internal] load build definition from Dockerfile                                                                 0.0s
=> => transferring dockerfile: 366B                                                                                 0.0s
=> [internal] load metadata for docker.io/library/ubuntu:20.04                                                      0.7s
=> [internal] load .dockerignore                                                                                    0.0s
=> => transferring context: 2B                                                                                      0.0s
=> [1/9] FROM docker.io/library/ubuntu:20.04@sha256:874aca52f79ae5f8258faff03e10ce99ae836f6e7d2df6ecd3da5c1cad3a91  0.0s
=> [internal] load build context                                                                                    0.0s
=> => transferring context: 735B                                                                                    0.0s
=> CACHED [2/9] RUN apt update                                                                                      0.0s
=> CACHED [3/9] RUN apt install -y gcc g++ cmake                                                                    0.0s
=> CACHED [4/9] COPY ./banking/ ./                                                                                  0.0s
=> CACHED [5/9] RUN cmake -S ./ -B ./build/                                                                         0.0s
=> CACHED [6/9] RUN cmake --build build                                                                             0.0s
=> CACHED [7/9] RUN groupadd -r sample && useradd -r -g sample sample                                               0.0s
=> exporting to image                                                                                               0.0s
=> => exporting layers                                                                                              0.0s
=> => writing image sha256:d6f8d6d5ff43d3137f7e15ca4012321b50042fd67c810ba908d62113d40a3fc0                         0.0s
=> => naming to docker.io/library/banking                                                                           0.0s

View build details: docker-desktop://dashboard/build/desktop-linux/desktop-linux/xq4mhxekox05e0vk9tsjsaeh8

What's Next?
  1. Sign in to your Docker account → docker login
  2. View a summary of image vulnerabilities and recommendations → docker scout quickview
```

```shell
$ docker run banking
```
```shell
Running main() from /build/_deps/googletest-src/googletest/src/gtest_main.cc
[==========] Running 10 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 6 tests from Account
[ RUN      ] Account.Mock
[       OK ] Account.Mock (0 ms)
[ RUN      ] Account.Init
[       OK ] Account.Init (0 ms)
[ RUN      ] Account.GetBalance
[       OK ] Account.GetBalance (0 ms)
[ RUN      ] Account.ChangeBalance
[       OK ] Account.ChangeBalance (0 ms)
[ RUN      ] Account.Lock
[       OK ] Account.Lock (0 ms)
[ RUN      ] Account.Unlock
[       OK ] Account.Unlock (0 ms)
[----------] 6 tests from Account (0 ms total)

[----------] 4 tests from Transaction
[ RUN      ] Transaction.Mock
[       OK ] Transaction.Mock (0 ms)
[ RUN      ] Transaction.Init
[       OK ] Transaction.Init (0 ms)
[ RUN      ] Transaction.Make
[       OK ] Transaction.Make (0 ms)
[ RUN      ] Transaction.SaveToDataBase
[       OK ] Transaction.SaveToDataBase (0 ms)
[----------] 4 tests from Transaction (0 ms total)

[----------] Global test environment tear-down
[==========] 10 tests from 2 test suites ran. (1 ms total)
[  PASSED  ] 10 tests.
```
