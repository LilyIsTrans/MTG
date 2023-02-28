# MTG Deck Analyzer

This program allows you to analyze the probability of drawing certain combinations of cards in one's initial hand in Magic: The Gathering (and other card games).
The interface is admittedly somewhat ugly, but quite minimal to avoid distraction.

The probability calculation is based on the hypergeometric probability function, further reading on which can be found [here](https://stattrek.com/probability-distributions/hypergeometric).

This project uses several libraries published under the MIT license, including [Dear ImGUI](https://github.com/ocornut/imgui), [Walnut](https://github.com/TheCherno/Walnut), and [WalnutAppTemplate](https://github.com/TheCherno/WalnutAppTemplate).
Additionally, this project uses [GLFW](https://www.glfw.org/), which is published under a separate license.

## How to use
### Building from source
  Clone this repository recursively:
  ```
  git clone --recursive https://github.com/Rilazy/MTG
  ```
  If you're building on Windows for Visual Studio, you can navigate to the scripts directory and run `setup.bat` to have premake generate the appropriate project files. Otherwise, you'll need to figure out your own premake command for your platform.
### Pre-built releases!
  A first for me! I've made some pre-compiled releases available. Make sure the dll and exe are in the same directory and run! Couldn't be much simpler (unless you get a Windows SmartScreen error; I'm not important enough to have my own SSL certificate.)
