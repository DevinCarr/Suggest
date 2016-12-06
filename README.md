Suggest
=============

A simple commandline tool to provide auto suggestions via [Bing Autosuggest API](https://www.microsoft.com/cognitive-services/en-us/bing-autosuggest-api).

```
$ s hello world
Suggest (v1):
"hello world"
"hello world java"
"hello world history"
"hello world c++"
"hello world example"
"hello world baby"
"hello world lyrics"
"helloworld inc"
```

## Requirements:
- make
- C++11 compiler (gcc/clang)
- libcurl
- API key for [Bing Autosuggest](https://www.microsoft.com/cognitive-services/en-us/bing-autosuggest-api)

To start, a `auth.h` file must be created in the source directory.

`auth.h` must contain your API key, for example:
```
#define AUTHPWD "ajsd908f09as8d098as09d"
```

## Build
```
make
```

To install to `/usr/local/bin/`: `make install`

## License
Copyright © 2016 Devin Carr

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
