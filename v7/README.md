# Take Two v0.5

## Let's add continuous integration using Travis CI

For starters, go to https://travis-ci.com and log in using your GitHub credentials. If you haven't already, grant Travis CI access to your GitHub repository.

Create a file in your project folder named `.travis.yml`

```bash
take_two
├── include
│   └── take_two
│       └── take_two.hpp
├── src
│   ├── CMakeLists.txt
│   └── take_two.cpp
├── example
│   ├── CMakeLists.txt
│   └── example.cpp
├── tests
│   ├── CMakeLists.txt
│   └── test_take_two.cpp
├── docs
│   ├── CMakeLists.txt
│   └── main.md
├── README.md
├── CMakeLists.txt
├── .travis.yml
└── .gitignore
```

This yaml file will tell Travis CI how to test your project and make sure everything's in working order.

This is done using a set of instructions that tells the virtual machine at Travis CI what steps to perform in order to run your project's unit tests

```yaml
language: cpp

compiler:
  - gcc
  - clang

before_script:
  - mkdir build
  - cd build
  - cmake -DTESTS=TRUE ..

script: make && make test
```

After pushing your changes to your GitHub repository, navigate to https://www.travis-ci.com to watch your build get tested in real time.

If you want, you can have Travis CI email you whenever your build fails.

Once your build succeeds, you can show off your achievement by clicking on the status image next to the repository name on Travis CI, setting the format to Markdown, and copying the result to the top of your `README.md` file. The result will look like:

[![Build Status](https://travis-ci.com/jeffmm/take_two.svg?branch=master)](https://travis-ci.com/jeffmm/take_two)

Now all you have left to do is write a brief explanation about your project in your README and add a LICENSE.

Congratulations, your project now looks pro!
