# include <Siv3D.hpp> // OpenSiv3D v0.6.9

Image MakeImage()
{
	return Image{ 600,600,Color{ 63, 127, 255 } };
}


void Main()
{
	// ウインドウサイズの変更
	Window::Resize(1000, 600);

	// キャンバスのサイズ
	constexpr Size canvasSize{ 600,600 };

	// ペンの太さ
	double thickness = 5;

	// ペンの色
	HSV penColor = Palette::Orange;

	// 書き込み用の画像データを用意
	Image image{ canvasSize,Palette::White };

	// 表示用のテクスチャ（内容を更新するのでDynamicTexture）
	DynamicTexture texture{ image };

	while (System::Update())
	{
		SimpleGUI::Headline(U"Color", Vec2{ 650,10 });
		SimpleGUI::ColorPicker(penColor, Vec2{ 650,50 });

		SimpleGUI::Headline(U"Thickness", Vec2{ 650,200 });
		SimpleGUI::Slider(U"{:.2f}"_fmt(thickness), thickness, 1.0, 10.0, Vec2{ 650,240 });

		SimpleGUI::Headline(U"Tool", Vec2{ 900,10 });
		if (SimpleGUI::Button(U"Fill", Vec2{ 900,60 })) {
			image.fill(penColor);
			texture.fill(image);
		}

		// Eキーで消しゴム
		if (KeyE.pressed())
		{
			penColor = Palette::White;
		}

		if (MouseL.pressed())
		{
			// 書き込む線の始点は直前のフレームのマウスカーソル座標
			// （初回はタッチ操作時の座標のジャンプを防ぐため、現在のマウスカーソル座標にする）
			const Point from = (MouseL.down() ? Cursor::Pos() : Cursor::PreviousPos());

			// 書き込む線の終点は現在のマウスカーソル座標
			const Point to = Cursor::Pos();

			// image に線を書き込む
			Line{ from, to }.overwrite(image, thickness, penColor);

			// 書き込み終わった image でテクスチャを更新
			texture.fill(image);
		}
		// 描いたものを消去するボタンが押されたら
		if (SimpleGUI::Button(U"Clear", Vec2{ 650, 300 }, 120))
		{
			// 画像を白で塗りつぶす
			image.fill(Palette::White);

			// 塗りつぶし終わった image でテクスチャを更新
			texture.fill(image);
		}

		// Saveボタンが押されたら画像を保存
		if (SimpleGUI::Button(U"Save", Vec2{ 650,360 }, 120))
		{
			image.save(U"image1.png");
		}

		// テクスチャを表示
		texture.draw();
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
