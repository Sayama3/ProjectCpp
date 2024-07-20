#ifndef PROJECTCPP_LOCALCOMMANDS_HPP
#define PROJECTCPP_LOCALCOMMANDS_HPP

#include "Commands.hpp"
#include "ImageTreatments.hpp"
#include "TemplatedCommands.hpp"

namespace Pic {
	class SobelFilterHCommand : public TCommandNoParam<SobelFilterHCommand> {
		PC_IMPL_NO_PARAM_COMMAND(SobelFilterHCommand, LocalTransformation::sobelH, "sobelH")
	};
	class SobelFilterVCommand : public TCommandNoParam<SobelFilterVCommand> {
		PC_IMPL_NO_PARAM_COMMAND(SobelFilterVCommand, LocalTransformation::sobelV, "sobelV");
	};
	class SobelNormCommand : public TCommandNoParam<SobelNormCommand> {
		PC_IMPL_NO_PARAM_COMMAND(SobelNormCommand, LocalTransformation::sobelNorm, "sobelNorm");
	};
	class SharpeningCommand : public TCommandNoParam<SharpeningCommand> {
		PC_IMPL_NO_PARAM_COMMAND(SharpeningCommand, LocalTransformation::sharpening, "sharpen");
	};
	class GaussianBlurCommand : public TCommandNoParam<GaussianBlurCommand> {
		PC_IMPL_NO_PARAM_COMMAND(GaussianBlurCommand, LocalTransformation::gaussianBlur, "gaussianBlur");
	};
	class MeanBlurCommand : public IntCommand<MeanBlurCommand> {
		PC_IMPL_INT_COMMAND(MeanBlurCommand, LocalTransformation::meanBlur, "meanBlur");
	};
	class ErodeCommand : public IntCommand<ErodeCommand> {
		PC_IMPL_INT_COMMAND(ErodeCommand, LocalTransformation::erode, "erode");
	};
	class DilateCommand : public IntCommand<DilateCommand> {
		PC_IMPL_INT_COMMAND(DilateCommand, LocalTransformation::dilate, "dilate");
	};
	class MedianCommand : public IntCommand<MedianCommand> {
		PC_IMPL_INT_COMMAND(MedianCommand, LocalTransformation::median, "median");
	};
	class MorpholicGradientCommand : public IntCommand<MorpholicGradientCommand> {
		PC_IMPL_INT_COMMAND(MorpholicGradientCommand, LocalTransformation::morphologicGradient, "morphologicGradient");
	};
	class LocalConstrastCommand : public IntFloatCommand<LocalConstrastCommand> {
		PC_IMPL_INT_FLT_COMMAND(LocalConstrastCommand, LocalTransformation::localConstrast, "localContrast");
	};
	class MeanShiftCommand : public IntFloatCommand<MeanShiftCommand> {
		PC_IMPL_INT_FLT_AS_INT_COMMAND(MeanShiftCommand, LocalTransformation::meanShift, "meanShift");
	};
	class AdpatativeThresholdCommand : public IntFloatCommand<AdpatativeThresholdCommand> {
		PC_IMPL_INT_FLT_AS_INT_COMMAND(AdpatativeThresholdCommand, LocalTransformation::adaptiveThreshold, "adThresh");
	};

	//TODO localConstrast with float + N and meanShift+adpatative THreshold with int + N
	static inline void AddLocalCommands(std::vector<CommandCreator> &commands) {
		commands.insert(commands.end(), {
												PC_COMMAND_CREATOR(SobelFilterHCommand),
												PC_COMMAND_CREATOR(SobelFilterVCommand),
												PC_COMMAND_CREATOR(SobelNormCommand),
												PC_COMMAND_CREATOR(SharpeningCommand),
												PC_COMMAND_CREATOR(GaussianBlurCommand),
												PC_COMMAND_CREATOR(MeanBlurCommand),
												PC_COMMAND_CREATOR(ErodeCommand),
												PC_COMMAND_CREATOR(DilateCommand),
												PC_COMMAND_CREATOR(MedianCommand),
												PC_COMMAND_CREATOR(MorpholicGradientCommand),
												PC_COMMAND_CREATOR(LocalConstrastCommand),
												PC_COMMAND_CREATOR(MeanShiftCommand),
												PC_COMMAND_CREATOR(AdpatativeThresholdCommand),

										});
	}
}// namespace Pic
#endif//PROJECTCPP_LOCALCOMMANDS_HPP
