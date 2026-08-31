#pragma once
#include "RendererComponent.h"
#include "Resources/Resource.h"
#include "Math/Rect.h"
#include "Renderer/Texture.h"

namespace nu
{
	class SpriteRendererComponent : public RendererComponent
	{
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent);

		void Start() override;

		void Draw(const class Renderer& renderer) override;

		virtual void Read(const json::value_t& value) override;

		const Vector2& GetSize() const { return m_size; }

		void SetFlipH(bool flip = true) { m_flipH = flip; }
		bool GetFlipH() const { return m_flipH; }

	protected:
		res_t<Texture> m_texture;
		std::string m_textureName;
		Rect m_sourceRect;
		Vector2 m_size{ 0.0f, 0.0f };
		bool m_flipH = false;
	};
}