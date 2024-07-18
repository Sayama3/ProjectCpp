//
// Created by ianpo on 18/07/2024.
//

#pragma once

namespace PC
{
	class Panel
	{
	public:
		virtual ~Panel() = default;
	public:
		virtual void Begin() {}
		virtual void Update(float dt) {}
		virtual void PostUpdate(float dt) {}
		virtual void End() {}
	};
}