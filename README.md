keening
=======

## Synopsis
This program is a minimalistic command line pastebin designed to be used
with `ssh`.

`keening` reads from stdin and writes data to a temporary file
(no arguments) or a named one (one argument). It then prints the URL
pointing to the paste.

Anything else (deleting temporary files, for example) is up to the user
to implement. You could use something like this in your `crontab`:

```crontab
0 */6 * * * find /var/www/paste/t/ -type f -mmin +360 -delete
```

## Installation

Use `make install`.

Keep in mind that `keening` is supposed to be installed on the host that will
be serving the pastes.

You can also use the ebuild in vehk/pramantha.

## Usage

```bash
emerge --info | ssh $host keening
```

```bash
ls -l | ssh $host keening persistent-paste
```

## Configuration
Edit `config.h` and rebuild.

## License
See `LICENSE` for licensing information. The short version: keening is released under BSD-3

This is software is written by Wolfgang Müller https://vehk.de, all credits go to him.