# MicroTools

This repository will serve as a home for all my embedded tools. A toolkit... an SDK... whatever you want to call it; this repo is where I intend to house code for embedded modules and code to simplify microcontroller SDK's.

## Using the repo

Everything here is meant to be suplemental libaries. None of this content is meant to serve as standalone projects. This means this leaves you with a few options for intended use.

1. Do your own thing... import however you see fit after downloading the content
2. Bring it into your CMake configured project via FetchContent. (I plan to model this after the raspberry pi pico sdk and how it handled its cmake/importing)

## Current content

I'm working mostly on raspberry pi pico's moving forward. I like how linux friendly they are, how low level they are, and their cost. So, if you are looking for arduino os ESP-32 boards there aren't any plans - on my part - to add anything for them until a need drives the work.

## Repo Structure

There are 3 main folders that all of the content will be parsed into.

### 00-MicroTools

Here is where tools to make microcontroller operation easier. The purpose - at this point - is to abstract more complex setup/steps into higher level function calls. An example of the content to find here:

To set up I2C on the raspberry pi pico you need to perform the following steps:
1. Set the pin functionality of the desired pins
2. Set the pull up's/down's of the pins
3. Initialize the I2C bus

The first two steps are a bit verbose for the way I want my code to read. So a higher level parent function that does all of these steps is preferable. This is the calibur of function I intend to put in this section.

### 01-Modules

Here will be libaries to support modules, components, or any other external hardware I stumble upon.

### 02-Examples

Here is where I might end up putting simple sample use cases of the libraries developed in this repo.
parameters will be put in place to prevent these from being built unless the user desires. So, pay attention to your CMake if you want these examples built.
