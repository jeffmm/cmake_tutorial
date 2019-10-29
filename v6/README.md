# Building a Cookie-Cutter

So far, we've been building a repo with a basic pattern:

```bash
project_name
├── include
│   └── project_name
│       └── lib.hpp
├── src
│   ├── CMakeLists.txt
│   └── lib.cpp
├── example
│   ├── CMakeLists.txt
│   └── example.cpp
├── tests
│   ├── CMakeLists.txt
│   └── test_lib.cpp
├── docs
│   ├── CMakeLists.txt
│   └── main.md
├── README.md
├── CMakeLists.txt
├── .travis.yml
└── .gitignore
```

It would be great if we can quickly scaffold a future project using this same pattern. That's what [Cookiecutter](https://github.com/audreyr/cookiecutter) is for.

Assuming you have Python 3 installed, you can install cookiecutter with

```bash
pip3 install cookiecutter
```

Then quickly scaffold a git repository using

```bash
cookiecutter https://github.com/jeffmm/cmake-project-cookiecutter
```

or equivalently

```bash
cookiecutter gh:jeffmm/cmake-project-cookiecutter
```

You will receive some prompts on the command line, such as the name of your project, etc. Once you finish filling them out, cookiecutter will scaffold your new project for you! The only thing left to do is register it as a git repo and push it to a remote repository.
