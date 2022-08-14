# Table of content 

* [Overview](#overview)
* [Usage](#usage)
* [Key board shortcuts](#keyboard shortcuts)

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

<div style="padding:75% 0 0 0;position:relative;"><iframe src="https://player.vimeo.com/video/654815518?h=e25c3c28a4&amp;badge=0&amp;autopause=0&amp;player_id=0&amp;app_id=58479" frameborder="0" allow="autoplay; fullscreen; picture-in-picture" allowfullscreen style="position:absolute;top:0;left:0;width:100%;height:100%;" title="vid-1.mp4"></iframe></div><script src="https://player.vimeo.com/api/player.js"></script>

* Adding/removing videos from collection 

<div style="padding:75% 0 0 0;position:relative;"><iframe src="https://player.vimeo.com/video/654816200?h=03454c51db&amp;badge=0&amp;autopause=0&amp;player_id=0&amp;app_id=58479" frameborder="0" allow="autoplay; fullscreen; picture-in-picture" allowfullscreen style="position:absolute;top:0;left:0;width:100%;height:100%;" title="vid-2.mp4"></iframe></div><script src="https://player.vimeo.com/api/player.js"></script>

* Adding/removing tags 

<div style="padding:75% 0 0 0;position:relative;"><iframe src="https://player.vimeo.com/video/654816351?h=74839c8386&amp;badge=0&amp;autopause=0&amp;player_id=0&amp;app_id=58479" frameborder="0" allow="autoplay; fullscreen; picture-in-picture" allowfullscreen style="position:absolute;top:0;left:0;width:100%;height:100%;" title="vid-3.mp4"></iframe></div><script src="https://player.vimeo.com/api/player.js"></script>

* Adding/changing location and going through the map

<div style="padding:75% 0 0 0;position:relative;"><iframe src="https://player.vimeo.com/video/654816576?h=5e92d73429&amp;badge=0&amp;autopause=0&amp;player_id=0&amp;app_id=58479" frameborder="0" allow="autoplay; fullscreen; picture-in-picture" allowfullscreen style="position:absolute;top:0;left:0;width:100%;height:100%;" title="vid-4.mp4"></iframe></div><script src="https://player.vimeo.com/api/player.js"></script>

* Seeking through videos 

<div style="padding:75% 0 0 0;position:relative;"><iframe src="https://player.vimeo.com/video/654816634?h=e75079ff42&amp;badge=0&amp;autopause=0&amp;player_id=0&amp;app_id=58479" frameborder="0" allow="autoplay; fullscreen; picture-in-picture" allowfullscreen style="position:absolute;top:0;left:0;width:100%;height:100%;" title="vid-5.mp4"></iframe></div><script src="https://player.vimeo.com/api/player.js"></script>

* Searching through videos 

<div style="padding:75% 0 0 0;position:relative;"><iframe src="https://player.vimeo.com/video/654816700?h=f47514f497&amp;badge=0&amp;autopause=0&amp;player_id=0&amp;app_id=58479" frameborder="0" allow="autoplay; fullscreen; picture-in-picture" allowfullscreen style="position:absolute;top:0;left:0;width:100%;height:100%;" title="vid-6.mp4"></iframe></div><script src="https://player.vimeo.com/api/player.js"></script>

* Sorting videos (ascend and descend) 

<div style="padding:75% 0 0 0;position:relative;"><iframe src="https://player.vimeo.com/video/654816774?h=54fb177d31&amp;badge=0&amp;autopause=0&amp;player_id=0&amp;app_id=58479" frameborder="0" allow="autoplay; fullscreen; picture-in-picture" allowfullscreen style="position:absolute;top:0;left:0;width:100%;height:100%;" title="vid-7.mp4"></iframe></div><script src="https://player.vimeo.com/api/player.js"></script>

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

