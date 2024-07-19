//
// Created by ianpo on 19/07/2024.
//

#pragma once

#include "Commands.hpp"
#include "GeometricTransformation.hpp"

namespace Pic {
	class FlipHorizontalCommand : public Command {
	public:
		FlipHorizontalCommand(std::string variableSrc, std::string variableTrg);
		virtual ~FlipHorizontalCommand() = default;
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(Image img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource, variableTarget;
	//(const Image& img);
	};


	class FlipVerticalCommand : public Command {
	public:
		FlipVerticalCommand(std::string variableSrc, std::string variableTrg);
		virtual ~FlipVerticalCommand() = default;
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(Image img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource, variableTarget;
	//(const Image& img);
	};


	class Rotate90Command : public Command {
	public:
		Rotate90Command(std::string variableSrc, std::string variableTrg);
		virtual ~Rotate90Command() = default;
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(Image img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource, variableTarget;
	//(const Image& img);
	};


	class CropCommand : public Command {
	public:
		CropCommand(std::string variableSrc, std::string variableTrg, uint32_t top, uint32_t left, uint32_t bottom, uint32_t right);
		virtual ~CropCommand() = default;
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(Image img) override;
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
		[[nodiscard]] virtual Image Execute(Image img) override;
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
		[[nodiscard]] virtual Image Execute(Image img) override;
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
		[[nodiscard]] virtual Image Execute(Image img) override;
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
		[[nodiscard]] virtual Image Execute(Image img) override;
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
		[[nodiscard]] virtual Image Execute(Image img) override;
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


	class ZoomCommand : public Command {
	public:
		ZoomCommand(std::string variableSrc, std::string variableTrg, float factor);
		virtual ~ZoomCommand() = default;
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(Image img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource, variableTarget;
		float factor;
	};

	/// Function to add all the geometrics Commands to the list of command
	static inline void AddGeometricCommands() {
		s_Command.insert(s_Command.end(), {
			{FlipHorizontalCommand::Compare, FlipHorizontalCommand::Create, FlipHorizontalCommand::Save},
			{FlipVerticalCommand::Compare, FlipVerticalCommand::Create, FlipVerticalCommand::Save},
			{Rotate90Command::Compare, Rotate90Command::Create, Rotate90Command::Save},
			{CropCommand::Compare, CropCommand::Create, CropCommand::Save},
			{TranslateCommand::Compare, TranslateCommand::Create, TranslateCommand::Save},
			{ResizeCommand::Compare, ResizeCommand::Create, ResizeCommand::Save},
			{ShearCommand::Compare, ShearCommand::Create, ShearCommand::Save},
			{RotateCommand::Compare, RotateCommand::Create, RotateCommand::Save},
			{RemapCommand::Compare, RemapCommand::Create, RemapCommand::Save},
			{ZoomCommand::Compare, ZoomCommand::Create, ZoomCommand::Save},
		  });
	}


}// namespace Pic
