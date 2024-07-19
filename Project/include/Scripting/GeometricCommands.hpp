//
// Created by ianpo on 19/07/2024.
//

#pragma once

#include "Commands.hpp"
#include "TemplatedCommands.hpp"
#include "GeometricTransformation.hpp"

namespace Pic {
	class FlipHorizontalCommand : public TCommandNoParam<FlipHorizontalCommand>
	{
		PC_IMPL_NO_PARAM_COMMAND(FlipHorizontalCommand, GeometricTransformation::FlipHorizontal, "flip horizontal");
	};

	class FlipVerticalCommand : public TCommandNoParam<FlipVerticalCommand>
	{
		PC_IMPL_NO_PARAM_COMMAND(FlipVerticalCommand, GeometricTransformation::FlipVertical, "flip vertical");
	};

	class ZoomCommand : public FloatCommand<ZoomCommand>
	{
		PC_IMPL_FLT_COMMAND(ZoomCommand,::GeometricTransformation::Zoom, "zoom")
	};

	class Rotate90Command : public TCommandNoParam<Rotate90Command>
	{
		PC_IMPL_NO_PARAM_COMMAND(Rotate90Command,::GeometricTransformation::Rotate90, "rotate90")
	};


	class CropCommand : public Command {
	public:
		CropCommand(std::string variableSrc, std::string variableTrg, uint32_t top, uint32_t left, uint32_t bottom, uint32_t right);
		virtual ~CropCommand() = default;
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(const Image& img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource, variableTarget;
		uint32_t top, left, bottom, right;
	//(const Image& img, uint32_t top, uint32_t left, uint32_t bottom, uint32_t right);
	};


	class TranslateCommand : public Command {
	public:
		TranslateCommand(std::string variableSrc, std::string variableTrg, uint32_t decalX, uint32_t decalY);
		virtual ~TranslateCommand() = default;
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(const Image& img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource, variableTarget;
		uint32_t decalX, decalY;
	};


	class ResizeCommand : public Command {
	public:
		ResizeCommand(std::string variableSrc, std::string variableTrg, uint32_t newWidth, uint32_t newHeight);
		virtual ~ResizeCommand() = default;
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(const Image& img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource, variableTarget;
		uint32_t newWidth, newHeight;
	};


	class ShearCommand : public Command {
	public:
		ShearCommand(std::string variableSrc, std::string variableTrg, uint32_t decalX, uint32_t decalY);
		virtual ~ShearCommand() = default;
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(const Image& img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource, variableTarget;
		uint32_t decalX, decalY;
	};


	class RotateCommand : public Command {
	public:
		RotateCommand(std::string variableSrc, std::string variableTrg, float angleDegree, uint32_t centerX, uint32_t centerY);
		virtual ~RotateCommand() = default;
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(const Image& img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource, variableTarget;
		float angleDegree;
		uint32_t centerX, centerY;
	};


	class RemapCommand : public Command {
	public:
		RemapCommand(std::string variableSrc, std::string variableTrg, std::vector<Vec2UI> remap);
		virtual ~RemapCommand() = default;
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(const Image& img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string ArrayToString() const;
		std::string variableSource, variableTarget;
		std::vector<Vec2UI> remap;
	};


	/// Function to add all the geometrics Commands to the list of command
	static inline void AddGeometricCommands(std::vector<CommandCreator>& commands) {
		commands.insert(commands.end(), {
			PC_COMMAND_CREATOR(FlipHorizontalCommand),
			PC_COMMAND_CREATOR(FlipVerticalCommand),
			PC_COMMAND_CREATOR(Rotate90Command),
			PC_COMMAND_CREATOR(CropCommand),
			PC_COMMAND_CREATOR(TranslateCommand),
			PC_COMMAND_CREATOR(ResizeCommand),
			PC_COMMAND_CREATOR(ShearCommand),
			PC_COMMAND_CREATOR(RotateCommand),
			PC_COMMAND_CREATOR(RemapCommand),
			PC_COMMAND_CREATOR(ZoomCommand),
		  });
	}


}// namespace Pic
