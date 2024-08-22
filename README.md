c++による2次元移流拡散方程式シミュレーションのプログラムです.
visual studio 2022で作成しました.
フォルダ内のソリューションファイルをvisual studio 2022で動かことで二次元移流拡散方程式のシミュレーションを実行できます
<br>
簡単なマニュアル
<br>
1:二次元計算領域を決める(xb,xt,yb,ytの4点の座標を入力)
<br>
2:x,y方向の要素数を入力
<br>
3:時間ステップの刻み幅dt, 計算終了ステップ, サンプルステップ数を入力
<br>
4:境界条件を定める(現在初期分布を1パターンしか用意できてないため,流入値->1と入力してください)
<br>
5：定常流速cx,cyと拡散係数alphaを入力
<br>
6:時間進行スキームの決定(陽解法:方程式を陽的に解く, 早い, 条件により計算が破綻する, 陰解法:方程式を陰的に解く,連立方程式を使う, 遅い, 結果が破綻しにくい)
<br>
7:C:/Result/2d_advection_diffusion_eq_calculation/../result/data n　にcsvファイルでサンプルステップ数ごとに結果を保存する
<br>

有限要素法や陰解法,陽解法についての詳しいマニュアルは作成中です.



