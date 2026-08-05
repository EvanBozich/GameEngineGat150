#pragma once
#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <SDL3_image/SDL_image.h>
#include "Texture.h"
#include "Model.h"
#include "Transform.h"


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

		void DrawTexture(const class Texture& texture, float x, float y);
		void DrawTexture(const class Texture& texture, float x, float y, float angle, float scale = 1.0f, bool flipH = false);

	private :
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;


	};
}