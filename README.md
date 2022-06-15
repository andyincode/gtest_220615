```
$ mkdir chansik.yun
$ cd chansik.yun



$ wget https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
$ tar xvf release-1.11.0.tar.gz
$ rm release-1.11.0.tar.gz
$ mv googletest-release-1.11.0 googletest

$ ./fuse_gtest_files.py ~/chansik.yun
$ cd ~/chansik.yun

$ g++ -c gtest/gtest-all.cc -I.
$ g++ -c main.cpp -I. 


$ g++ main.o gtest-all.o -pthread
$ ./a.out
```

# Google Test 라이브러리 빌드 방법
```
$ g++ -c gtest/gtest-all.cc -I.
> gtest-all.o

$ g++ -c ./googletest/googletest/src/gtest_main.cc -I.
$ ar rcv libgtest.a gtest-all.o gtest_main.o


build.sh
$ chmod +x build.sh

```



* 라이브러리
  - 동적 라이브러리: libgtest.so
    : 실행 파일에 라이브러리 코드가 포함되지 않습니다.
      실행 시점에 로드해서 사용합니다.
      라이브러리 코드가 변경되도 실행 파일을 다시 만들 필요가 없습니다.
      실행 파일이 수행되기 위해서는 의존하는 동적 라이브러리가 별도로 제공되어야 합니다.

  - 정적 라이브러리: libgtest.a => 권장
    : 실행 파일에 라이브러리의 모든 코드가 포함됩니다.
      라이브러리가 변경되면 실행 파일을 다시 만들어야 합니다.
      별도의 라이브러리의 의존성 없이 독립적인 실행이 가능합니다.




googletest
  |
  1. google test - xUnit Test Framework
  2. google mock - xUnit Test Framework + Test Double => *
