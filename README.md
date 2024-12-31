# The Ghosts of Blackwood Manor

![The Ghosts of Blackwood Manor is copyright (c) 2023 Stefan Vogt, Moonmist Entertainment. Screen taken from Atari ST version.](https://img.itch.zone/aW1hZ2UvMjM2MjcyNi8xNDE1OTkzOC5wbmc=/original/0%2B2WXR.png "The Ghosts of Blackwood Manor is copyright (c) 2023 Stefan Vogt, Moonmist Entertainment. Screen taken from Atari ST version.")

The Ghosts of Blackwood Manor is an award-winning interactive horror from Stefan Vogt, the acclaimed author of Hibernated Director's Cut. It is an ambitious and complex interactive fiction piece written in Infocom's advanced Z-machine version 5 format XZIP. The term z5 might be more familiar to some of you. Ghosts is available for a plethora of retro systems but also for modern PC. If you just want to play it, head over to [https://8bitgames.itch.io/ghosts](https://8bitgames.itch.io/ghosts) and grab yourself a copy. This repository is for educational purposes only.

## Code

The Ghosts of Blackwood Manor was created with [PunyInform](https://github.com/johanberntsson/PunyInform), a custom library by Fredrik Ramsberg and Johan Berntsson for Graham Nelson's Inform language. It is designed to be memory efficient and known to perform well on old hardware like the Commodore 64, ZX Spectrum, Atari ST, Commodore Amiga, or MS-DOS machines. Ghosts is intended to be built using the [Puny BuildTools](https://github.com/ByteProject/Puny-BuildTools), essentially a PunyInform CLI and retro disk image factory for Infocom Z-machine games.

The source is not found in a single .inf file, instead it spawns over multiple files. While this might be overwhelming on first sight, especially for those new to PunyInform, there is a valid reason why I did it this way. My code is designed to be super modular. I am basically "outsourcing" code that recurrs from game to game to separate files, so that the core .inf file allows me to be very focused on the game and not on glue code or repitition. Once you've made yourself comfortable with the way organized the source, I promise you will never look back. The essential files are: 

* ghosts.inf - the core game source
* moonmist.h - recurring code characteristic for a Moonmist release, grammar and subs are grouped
* punyhacks.h - contains PunyInform routine replacements and supplements, turn on/off as needed
* messages.h - a custom messages file, meant to replace the PunyInform library file
* abbrvs.h - custom abbreviations to optimize the compiled game size and speed

You will notice a more detailed information in every header. 

If you find the Ghosts source code useful in your aim to learn programming adventures with PunyInform, please send a donation via <https://8bitgames.itch.io/ghosts>.

## Notes in random Order

* While I think that the code in moonmist.h and punyhacks.h is well documented, the code in ghosts.inf sometimes lacks a bit of documentation. This is because I did not intend to share the Ghosts source initially. So, if you are stumbling upon a piece of code and you're wondering why I did this or that, just ask me in the support thread of the PunyInform Discord. I am getting old, so my brain does not remember everything as it used to, but I might have an answer for you.
* I am not the best Inform programmer. I think I am pretty solid but far from being on the same level as Fredrik or Johan. So if you see a smarter way of doing things, be proud of yourself but don't send me pull requests or other recommendations. I won't be improving the code other than providing bugfixes. Ghosts is considered feature complete and done.
* Regarding the custom messages.h file: the best way to make sure it is applied upon compilation (without harming any PunyInform library files) is using the [punycustom](https://github.com/ByteProject/Puny-BuildTools?tab=readme-ov-file#the-punycustom-folder) feature of the [Puny BuildTools](https://github.com/ByteProject/Puny-BuildTools). If you compile something else, be sure to remove the file again from the punycustom folder, otherwise the custom messages.h file will be used for the other game as well, which likely is not what you want. Smart people would probably automate this as part of the build script.

## Agreement

This source code is provided for personal, educational use only. You can read it, and copy the programming techniques, but you can't make derivative games.

The Ghosts of Blackwood Manor is copyright (c) 2023 Stefan Vogt, Moonmist Entertainment. It may be distributed freely, provided you link to [8bitgames.itch.io](https://8bitgames.itch.io). It may not be sold or included in any for-profit collection without written permission from the author.
