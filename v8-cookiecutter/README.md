# Scaffolding a project with Cookiecutter

So far, we've been building a repo with a basic pattern:

```bash
project_name
├── include
│   └── project_name
│       └── lib.hpp
├── src
│   ├── CMakeLists.txt
│   └── lib.cpp
├── examples
│   ├── CMakeLists.txt
│   └── example.cpp
├── thirdparty
│   ├── CMakeLists.txt
│   └── catch2
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
cookiecutter https://github.com/jeffmm/cmake_project_cookiecutter
```

or equivalently

```bash
cookiecutter gh:jeffmm/cmake_project_cookiecutter
```

You will receive some prompts on the command line, such as the name of your project, your GitHub username, etc. Once you finish answering, cookiecutter will scaffold your new project for you! All you have left to do is initialize the repo using `git init` and push the repo to a new repository on GitHub. 

Now you can get straight to coding!
