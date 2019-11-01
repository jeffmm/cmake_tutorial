# TakeTwo v0.5

## Let's add continuous integration using Travis CI

Now we are going to add continuous integration (CI), a development strategy that employs automated builds of our project to make sure everything is working and up-to-date. We will do this through a service called Travis CI that builds and tests our code every time we push new changes to GitHub.

For starters, go to https://travis-ci.com and log in using your GitHub credentials. Then follow the instructions on the website to grant Travis CI access to your GitHub repository.

Now create a file in your project folder named `.travis.yml`

```bash
take_two
├── include
│   └── take_two
│       └── take_two.hpp
├── src
│   ├── CMakeLists.txt
│   └── take_two.cpp
├── examples
│   ├── CMakeLists.txt
│   └── example.cpp
├── thirdparty
│   ├── CMakeLists.txt
│   └── catch2
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

If you want, you can have Travis CI email you whenever your build fails to let you know there's a problem.

Once your build succeeds, you can show off your achievement by clicking on the status image on your repository's build page at the Travis CI website, setting the format to Markdown, and copying the result to the top of your `README.md` file. The result will look like:

[![Build Status](https://travis-ci.com/jeffmm/take_two.svg?branch=master)](https://travis-ci.com/jeffmm/take_two)

To finish your project properly, add a project overview and install instructions to your README and then add a LICENSE. You can find options for a LICENSE on GitHub by navigating to your repository, clicking "Create new file" and entering LICENSE for the file name. You will see a new button appear, "Choose a license template," that will help you select a license that suits your needs.

Congratulations, your project now looks pro!
