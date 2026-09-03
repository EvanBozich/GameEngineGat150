#pragma once
#include "Texture.h"
#include "Model.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include <SDL3_image/SDL_image.h>


namespace nu 
{

	class Renderer
	{
	public :
		bool Initialize(const char* name, int width, int height);
		void Shutdown();

		void SetColorInt(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) const;
		void SetColorFloat(float r, float g, float b, float a = 1.0f) const;

		void Clear() const;
		void Present() const;

		void DrawPoint(float x, float y) const;
		void DrawFillRect(float x, float y, float w, float h) const;
		void DrawRect(float x, float y, float w, float h) const;
		void DrawLine(float x1, float y1, float x2, float y2) const;

		void DrawModel(const Model& model, const Transform& transform) const;

		friend class Text;
		friend class Texture;

		void DrawTexture(const class Texture& texture, float x, float y, float angle = 0.0f, float scale = 1.0f, bool flipH = false, const Vector2& origin = Vector2{0.5f, 0.5f}) const;
		void DrawTexture(const class Texture& texture, const struct Rect& source, float x, float y, float angle = 0.0f, float scale = 1.0f, bool flipH = false, const Vector2& origin = Vector2{ 0.5f, 0.5f }) const;

		void SetCamera(const Vector2& camera) { m_camera = camera; }
		void EnableCamera(bool enable = true) { m_cameraEnabled = enable; }

	private :
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
		bool m_cameraEnabled = true;
		Vector2 m_camera{ 0.0f, 0.0f };
		float m_width = 1280.0f;
		float m_height = 1024.0f;


	};
}