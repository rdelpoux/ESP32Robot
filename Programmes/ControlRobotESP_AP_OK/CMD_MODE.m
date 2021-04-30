% Click on text to reWrite file myParam.m
classdef CMD_MODE < Simulink.IntEnumType
enumeration
    CMD_INIT(0),
	CMD_MODE_OFF(1),
	CMD_MODE_OL(2),
	CMD_MODE_STEP(3),
	CMD_MODE_CL(4),
    end
end 