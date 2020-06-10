# github-username-c

This program takes GitHub usernames as input, fetches their account information by calling the [GitHub API](https://developer.github.com/v3/) and lets you choose to sort it by various fields.

## Setup
- Clone this repository by `git clone https://github.com/akshgpt7/github-username-c`.
- Install the `libcurl` dependency if you don't already have it:
On OS X, use homebrew and run `brew install curl`. On Ubuntu, `sudo apt-get install libcurl4-openssl-dev` will work. On Fedora, `sudo dnf libcurl-devel`.

## Usage
- After cloning, change working directory `cd github-username-c`.
- Run the following command to compile the source: `gcc -o github github.c -L. -lrequests -lcurl`.
- After compiling, to execute the program, run `./github`.

## Screenshots
![screenshot1](https://raw.githubusercontent.com/akshgpt7/github-username-c/master/screenshots/Screenshot%20from%202020-06-10%2018-23-56.png?token=AE3VYP27CXGRVJRPUVYP3ES65IJQ6)

![screenshot2](https://raw.githubusercontent.com/akshgpt7/github-username-c/master/screenshots/Screenshot%20from%202020-06-10%2018-24-34.png?token=AE3VYP7QM6ETGVSIMHYNVQK65IJXO)
