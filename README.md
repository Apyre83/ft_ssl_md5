# ft_ssl_md5

## Introduction
`ft_ssl_md5` is a C project inspired by the functionality of the OpenSSL library, specifically focused on recreating the hashing commands for MD5, SHA256, and Whirlpool. This project is part of the School 42 curriculum and includes additional enhancements (bonuses) beyond the base specifications.

## Table of Contents
- [Installation](#installation)
- [Features](#features)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Installation

To install `ft_ssl_md5`, clone this repository and use the Makefile to compile the project:

```bash
git clone https://github.com/Apyre83/ft_ssl_md5.git
cd ft_ssl_md5
make
```

This will create an executable named `ft_ssl` that can perform MD5, SHA256, and Whirlpool hashing.

## Features

`ft_ssl_md5` supports the following cryptographic hash functions:

- **MD5**: A widely used hash function producing a 32-character hexadecimal number.
- **SHA256**: Part of the SHA-2 family, produces a 256-bit hash, typically rendered as a 64-character hexadecimal number.
- **Whirlpool**: A hash designed by Vincent Rijmen and Paulo S. L. M. Barreto, which produces a 512-bit (64-byte) hash.

### Bonuses
- Support for processing multiple files and strings in a single command.
- A verbose mode that details the steps of the hashing process.

## Usage

Here is how to use the `ft_ssl` command to generate hashes:

```bash
# Generate an MD5 hash
./ft_ssl md5 filename.txt

# Generate a SHA256 hash
./ft_ssl sha256 filename.txt

# Generate a Whirlpool hash
./ft_ssl whirlpool filename.txt

# Hash from standard input
echo -n "Hello, world!" | ./ft_ssl md5
```

## Contributing

Contributions are welcome. If you have improvements or bug fixes, please fork the repository and submit a pull request. For substantial changes, please open an issue first to discuss what you would like to change.

## License

`ft_ssl_md5` is available under the MIT License. See the LICENSE file for more info.