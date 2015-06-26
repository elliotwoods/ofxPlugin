# Introduction

ofxPlugin lets you write an application with openFrameworks which can load in plugins which are also written in openFrameworks, e.g.:

* Application contains a vector of BaseShape
* Plugin has a class CircleShape which inherits BaseShape
* Application loads Plugin so that it can create instances of CircleShape

## Naming conventions:
* `Module` - A (non-abstract) class which the Plugin provides (this is the content of your plugin, your plugin may define 1 or more `Module`s)
* `ModuleBaseType` - A (abstract) class which the Module inherits from
* `Factory<Module>` - A class which can instantiate other classes, e.g. a `Factory<MyModule>` can create instances of `MyModule` class
* `FactoryRegister<ModuleBaseType>` - A class which contains a list of `Factory`s. All the `Factory`s inside this register will create `Module`s which inherit from `ModuleBaseType`.

# Requirements

Currently runs on oF 0.9.0 in Windows. OSX support coming later.
Tested on Visual Studio 2015.

# Todo

Auto-name handling (currently digging the names out of dumpbin logs).

# Notes

A `Factory` is something which instantiates classes for you. For each module (i.e. class type), you'll have one `Factory` which can instantiate that class at runtime.

ofxPlugin provides a `FactoryRegister` where you can store all these factories. When you load a plugin, it adds the factories from that plugin to the `FactoryRegister`

Your `ModuleBaseType` must be a non abstract class, i.e. it cannot have something like `virtual void draw() = 0;`. This hurts I know, but it's necessary for a factory model to work well.

Your plugin needs references to openframeworksLib (and anything else it references).
