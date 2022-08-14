# Table of content 

* [Overview](#overview)
* [Usage](#usage)
* [Key board shortcuts](#keyboard-shortcuts)

# Overview
* This software is targeted towards outdoor enthusiasts
* The source is located in ``mediaplayer/Player/`` 
* The videos are located in ``video`` 
* To compile and run:
```
qmake Player.pro && ./Player
``` 
* It is used to encapsulate a bunch of added videos into a collection such that each video will have:
  * Its chose location 
  * Its set of specified tags 
  * Its thumbnail which has the same name of the video but the format is different 
  * The length of the video 
* An example of a stored collection will be as follows:

```
home/a.MOV,home/a.png,00:00:18,manchester,cycling,mountains,view
home/b.MOV,home/b.png,00:00:15,leeds,sculpting,creative
home/c.MOV,home/c.png,00:00:11,london,club,party,fun
```

* We can see that each video has its own thumbnail such as ``a.MOV`` has ``a.png`` 
* Features
  * Open and save collections 
  * open multiple videos and view them   
  * Add/remove tags 
  * Change/add location to video 
  * Add/remove videos from collections
  * View the location of each video in the map 
  * The map automatically changes as you change the video 
  * Play/Pause/Stop the video 
  * Seek through the video 
  * Next and previous buttons to go though the videos 
  * Change the volume 
  * Have an overlay over the video that displays the current tag and location 
  * Displays an option such that you can chose which tag to remove 
  * Dynamic search 
    * Through video names
    * Through tags 
    * Through location 
    * Through location and tags 
  * Sorting 
    * Sort by name ascend or descending 
    * Sort by length ascend or descending 
    * Sort by location ascend or descending 

# Usage 

* Opening videos and collections 
[![Watch the video](https://img.youtube.com/vi/STuA3cx-154/maxresdefault.jpg)](https://youtu.be/STuA3cx-154)

* Adding/removing videos from collection 
[![Watch the video](https://img.youtube.com/vi/6abx3m7bres/maxresdefault.jpg)](https://youtu.be/6abx3m7bres)

* Adding/removing tags 
[![Watch the video](https://img.youtube.com/vi/RL7VXBIm8GE/maxresdefault.jpg)](https://youtu.be/RL7VXBIm8GE)

* Adding/changing location and going through the map
[![Watch the video](https://img.youtube.com/vi/Hz-vaPB32TE/maxresdefault.jpg)](https://youtu.be/Hz-vaPB32TE)

* Seeking through videos 
[![Watch the video](https://img.youtube.com/vi/K8tZo41-9S8/maxresdefault.jpg)](https://youtu.be/K8tZo41-9S8)

* Searching through videos 
[![Watch the video](https://img.youtube.com/vi/u8UcSvAtW0Q/maxresdefault.jpg)](https://youtu.be/u8UcSvAtW0Q)

* Sorting videos (ascend and descend) 
[![Watch the video](https://img.youtube.com/vi/V6QKl09ayTE/maxresdefault.jpg)](https://youtu.be/V6QKl09ayTE)

# Keyboard shortcuts 

<button type="button">Ctrl+O</button> $\Rightarrow$ **Open** a new **collection** of videos stored as a ``.txt`` file 

<button type="button">Ctrl+S</button> $\Rightarrow$ **Save** a new **collection** of videos stored as a ``.txt`` file 

<button type="button">Ctrl+V</button> $\Rightarrow$ **Add** a new **video** from the right side to collection 

<button type="button">Ctrl+Shift+V</button> $\Rightarrow$ **Remove** current playing **video** from the collection

<button type="button">Ctrl+T</button> $\Rightarrow$ **Add** a new **tag** to currently playing video 

<button type="button">Ctrl+Shift+T</button> $\Rightarrow$ **Remove** a **tag** from currently playing video  

<button type="button">Ctrl+L</button> $\Rightarrow$ **Add/Change** **location** of currently playing video 

<button type="button">Ctrl+H</button> $\Rightarrow$ Open the **help** file 

<button type="button">Space</button> $\Rightarrow$ **Play/Pause** current video 

<button type="button">Ctrl+Shift+F</button> $\Rightarrow$ **Full screen** 

<button type="button">Esc</button> $\Rightarrow$ Exists the full screen 

