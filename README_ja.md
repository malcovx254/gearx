*※　このプロジェクトは未完成です。*
## OpenGL(glut.h+glew.h)+OpenCSG 歯車に関する物体を描画するライブラリ 

機械式時計が好きな諸君のために、OpenGLとOpenCSGを使ったライブラリをつくりました。

### なぜOpenGLなのか？
本来、複雑な3Dモデルを描画する際には、Unity や Unreal、Blender などの
ツールを使うことが一般的です。

しかし、これらツールはメモリを多量に使用し、私の環境では動作しません。
そこで、軽量でも動作する OpenGL を選ぶこととなりました。


### メインコンテンツ
OpenGL で、機械式時計のパーツ（歯車・ゼンマイ・テンプなど）が
分解されて、再び組み上がっていくアニメーションを制作しています。
機械式時計のモデルは、ETA6497-1を参考にしました。

<br>
<img width="200" src="https://cdn.renderhub.com/jordaki3d/eta-2824-2-watch-movement/eta-2824-2-watch-movement-02.jpg">



### 何ができるか

display()関数に数行のコードを書くだけで、以下のものを描くことができます。
- 歯車 
<br>平歯車、ベベルギアなど
<br>
<img width="150" src="https://png.pngtree.com/png-clipart/20190516/original/pngtree-daily-gear-gear-effect-pattern-material-suppliesgear-iconmetalwheel-png-image_4007270.jpg">
- 機械式時計
<br>eta6497の懐中時計のアニメーション
<br>
<img width="150" src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTg_5nKoq3SVMeV05M7z_Lz22_EhHONgukBbg&s">
- UI
<br>ボタン、blenderの旋回gizmoのような便利ツール
<br>
<img width="200" src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQN7K-KaNCcu8vuxxxglDzqXB0wWdJKJzvx2w&s">


### 展望

将来的に、このプロジェクトはOpenGLからVulkanに移行することを目指しています。

### 参考
- [ETA6497技術シート](https://shopb2b.eta.ch/technicaldocuments/index/pdf/id/1631/)
- [youtube Disassembling ETA 6497](https://youtube.com/watch?time_continue=1&v=V7IJm3akfRY&embeds_referring_euri=https%3A%2F%2Fcalibercorner.com%2F&source_ve_path=MjM4NTE)