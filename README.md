# Banter
Banter is a toy programming language implementation via the C++ LLVM APIs.

## Installation and Use
In order to run the banter compiler on your system, you will need to install LLVM. <br>
You can do this on a MacOS device by using Homebrew.
```bash
brew install llvm
```
You can confirm the install and check which version by running the following,
```bash
brew list --versions LLVM
```
and furthermore add LLVM to your path variable with,
```bash
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
```

### Implementation Resources 
[1] [Monkey Language C++ Translation - Zhuzilin](https://github.com/zhuzilin/monkey), Orig. [Interpreter Book](https://interpreterbook.com/) <br>
[2] [LLVM Kaleidoscope](https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html)

