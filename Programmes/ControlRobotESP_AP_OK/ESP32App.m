classdef ESP32App < matlab.apps.AppBase

    % Properties that correspond to app components
    properties (Access = public)
        UIFigure               matlab.ui.Figure
        GridLayout             matlab.ui.container.GridLayout
        LeftPanel              matlab.ui.container.Panel
        ConnectButton          matlab.ui.control.Button
        CommandeButtonGroup    matlab.ui.container.ButtonGroup
        OffButton              matlab.ui.control.RadioButton
        StepButton             matlab.ui.control.RadioButton
        ClosedLoopButton       matlab.ui.control.RadioButton
        OpenLoopButton         matlab.ui.control.RadioButton
        SENDButton             matlab.ui.control.Button
        CmdEditFieldLabel      matlab.ui.control.Label
        CmdEditField           matlab.ui.control.NumericEditField
        SaveDataButton         matlab.ui.control.Button
        PlotterLabel           matlab.ui.control.Label
        Image                  matlab.ui.control.Image
        ClearDataButton        matlab.ui.control.Button
        Ref0EditFieldLabel     matlab.ui.control.Label
        Ref0EditField          matlab.ui.control.NumericEditField
        Ref1EditFieldLabel     matlab.ui.control.Label
        Ref1EditField          matlab.ui.control.NumericEditField
        Ref2EditFieldLabel     matlab.ui.control.Label
        Ref2EditField          matlab.ui.control.NumericEditField
        RobotIPEditFieldLabel  matlab.ui.control.Label
        RobotIPEditField       matlab.ui.control.EditField
        RightPanel             matlab.ui.container.Panel
        UIAxes_data1           matlab.ui.control.UIAxes
        UIAxes_data2           matlab.ui.control.UIAxes
        UIAxes_data3           matlab.ui.control.UIAxes
    end

    % Properties that correspond to apps with auto-reflow
    properties (Access = private)
        onePanelWidth = 576;
    end

    
    properties (Access = private)
        Property % Description
        t
        robot = 1
        time = 0
        ampl = 0
        myTimer
        plotLineD1           % Line object
        plotLineD2           % Line object
        plotLineD3           % Line object
        
        
        IP
        
        % Frame
        frameIn = Frame
        frameOut = Frame
        
        connected
        
        
    end
    
    methods (Access = private)
        
        function myTimerFcn(app,~,~)
            if(app.connected)
                if(app.t.NumBytesAvailable >=16)
                    data = read(app.t,16);
                    app.frameIn.Mark = data(1);
                    app.frameIn.Id = data(2);
                    app.frameIn.data1 = typecast(data(4:7),'int32');
                    app.frameIn.data2 = typecast(data(8:11),'int32');
                    app.frameIn.data3 = typecast(data(12:15),'int32');
                    
                    ydata = app.plotLineD1.YData;
                    ydata = circshift(ydata,1);
                    ydata(1) = flip(double(app.frameIn.data1)/1000.0);
                    app.plotLineD1.YData = ydata;
                    
                    ydata = app.plotLineD2.YData;
                    ydata = circshift(ydata,1);
                    ydata(1) = flip(double(app.frameIn.data2)/1000.0);
                    app.plotLineD2.YData = ydata;
                    
                    ydata = app.plotLineD3.YData;
                    ydata = circshift(ydata,1);
                    ydata(1) = flip(double(app.frameIn.data3)/1000.0);
                    app.plotLineD3.YData = ydata;
                end
            end
            
        end
    end
    

    % Callbacks that handle component events
    methods (Access = private)

        % Code that executes after component creation
        function StartUp(app)
            % Configure x- and y- axis
            fileID = fopen('robotnumber.h','r');
            
            a = fscanf(fileID,'%s');
            k = strfind( a , 'ROBOTNUMBER' );
            
            %            app.IP = str2double(a(k(3)+11:k(3)+13));
            
            app.RobotIPEditField.Value = strcat("192.168.4.1");
            
            
            app.UIAxes_data1.XLim = [0 6];
            app.UIAxes_data1.XDir = 'reverse';
            app.UIAxes_data1.YLim = [0 10];
            % Initial plot is all zeros
            app.plotLineD1 = plot(app.UIAxes_data1,0:0.01:6,zeros(1,601));
            
            % Configure x- and y- axis
            app.UIAxes_data2.XLim = [0 6];
            app.UIAxes_data2.XDir = 'reverse';
            app.UIAxes_data2.YLim = [0 30];
            % Initial plot is all zeros
            app.plotLineD2 = plot(app.UIAxes_data2,0:0.01:6,zeros(1,601));
            
            % Configure x- and y- axis
            app.UIAxes_data3.XLim = [0 6];
            app.UIAxes_data3.XDir = 'reverse';
            app.UIAxes_data3.YLim = [0 30];
            % Initial plot is all zeros
            app.plotLineD3 = plot(app.UIAxes_data3,0:0.01:6,zeros(1,601));
            
            
            % Create timer object
            app.myTimer = timer(...
                'ExecutionMode', 'fixedRate', ...    % Run timer repeatedly
                'Period', .01, ...                     % Period is 1 second
                'BusyMode', 'queue',...              % Queue timer callbacks when busy
                'TimerFcn', @app.myTimerFcn);      % Specify callback function
            
            % Init frame
            app.frameOut.Mark = 255;
            app.frameOut.Id = 1;
            app.frameOut.Cmd = 2;
            app.frameOut.data1 = 1;
            app.frameOut.data2 = 2;
            app.frameOut.data3 = 3;
            app.frameOut.CheckSum = 5;
            app.frameOut.Cmd = 1;
            app.CmdEditField.Value= double(app.frameOut.Cmd);
            app.connected = false;
        end

        % Callback function
        function AmplitudeSliderValueChanged(app, event)
            
        end

        % Changes arrangement of the app based on UIFigure width
        function updateAppLayout(app, event)
            currentFigureWidth = app.UIFigure.Position(3);
            if(currentFigureWidth <= app.onePanelWidth)
                % Change to a 2x1 grid
                app.GridLayout.RowHeight = {714, 714};
                app.GridLayout.ColumnWidth = {'1x'};
                app.RightPanel.Layout.Row = 2;
                app.RightPanel.Layout.Column = 1;
            else
                % Change to a 1x2 grid
                app.GridLayout.RowHeight = {'1x'};
                app.GridLayout.ColumnWidth = {281, '1x'};
                app.RightPanel.Layout.Row = 1;
                app.RightPanel.Layout.Column = 2;
            end
        end

        % Button pushed function: ConnectButton
        function ConnectButtonPushed(app, event)
                app.t = tcpclient(app.RobotIPEditField.Value,80,"ConnectTimeout",10);
                %flush(app.t);
                app.ConnectButton.BackgroundColor='green';
%                 
                 if strcmp(app.myTimer.Running, 'off')
                     start(app.myTimer);
                 end
%                 
                 app.connected = true;
%                 
            
            
            
            
            
            
            
        end

        % Callback function
        function StartButtonPushed(app, event)
            disp(app.time)
            write(app.t, [uint8(55) uint8(app.time) uint8(app.ampl)]);
        end

        % Callback function
        function timeEditFieldValueChanged(app, event)
            app.time = app.timeEditField.Value;
        end

        % Callback function
        function amplitudeEditFieldValueChanged(app, event)
            app.ampl = app.amplitudeEditField.Value;
            
        end

        % Callback function
        function RobotIPEditFieldValueChanged(app, event)
            app.robot = app.RobotIPEditField.Value;
            
        end

        % Callback function
        function PlotStartButtonPushed(app, event)
            % If timer is not running, start it
            
        end

        % Callback function
        function PlotStopButtonPushed(app, event)
            % Stop the timer
            stop(app.myTimer);
        end

        % Close request function: UIFigure
        function UIFigureCloseRequest(app, event)
            % Stop timer, then delete timer and app
            stop(app.myTimer);
            delete(app.myTimer);
            delete(app)
            
        end

        % Button pushed function: SENDButton
        function SENDButtonPushed(app, event)
            write(app.t, app.frameOut.formatframe());
        end

        % Selection changed function: CommandeButtonGroup
        function CommandeButtonGroupSelectionChanged(app, event)
            switch app.CommandeButtonGroup.SelectedObject.Text
                case 'Off'
                    app.frameOut.Cmd =1;%CMD_MODE.CMD_MODE_OFF;
                case 'OpenLoop'
                    app.frameOut.Cmd =2;%CMD_MODE.CMD_MODE_OL;
                case 'Step'
                    app.frameOut.Cmd =3;%CMD_MODE.CMD_MODE_STEP;
                case 'ClosedLoop'
                    app.frameOut.Cmd =4;%CMD_MODE.CMD_MODE_CL;
            end
            app.CmdEditField.Value= double(app.frameOut.Cmd);
            
        end

        % Button pushed function: SaveDataButton
        function SaveDataButtonPushed(app, event)
            ydata1 = app.plotLineD1.YData;
            ydata2 = app.plotLineD2.YData;
            ydata3 = app.plotLineD3.YData;
            data = [0:0.01:6; flip(ydata1); flip(ydata2); flip(ydata3)];
            %save data;
            %[FileName,PathName] = uiputfile(['mydata.mat',extensionString],'Save table data');
            
            save('data.mat','data');
        end

        % Button pushed function: ClearDataButton
        function ClearDataButtonPushed(app, event)
            app.plotLineD1 = plot(app.UIAxes_data1,0:0.01:6,zeros(1,601));
            app.plotLineD2 = plot(app.UIAxes_data2,0:0.01:6,zeros(1,601));
            app.plotLineD3 = plot(app.UIAxes_data3,0:0.01:6,zeros(1,601));
            
        end

        % Value changed function: Ref0EditField
        function Ref0EditFieldValueChanged(app, event)
            app.frameOut.data1 = int32(1000*app.Ref0EditField.Value);
        end

        % Value changed function: Ref1EditField
        function Ref1EditFieldValueChanged(app, event)
            app.frameOut.data2 = int32(1000*app.Ref1EditField.Value);
        end

        % Value changed function: Ref2EditField
        function Ref2EditFieldValueChanged(app, event)
            app.frameOut.data3 = int32(1000*app.Ref2EditField.Value);
            
        end
    end

    % Component initialization
    methods (Access = private)

        % Create UIFigure and components
        function createComponents(app)

            % Create UIFigure and hide until all components are created
            app.UIFigure = uifigure('Visible', 'off');
            app.UIFigure.AutoResizeChildren = 'off';
            app.UIFigure.Position = [100 100 846 714];
            app.UIFigure.Name = 'MATLAB App';
            app.UIFigure.CloseRequestFcn = createCallbackFcn(app, @UIFigureCloseRequest, true);
            app.UIFigure.SizeChangedFcn = createCallbackFcn(app, @updateAppLayout, true);

            % Create GridLayout
            app.GridLayout = uigridlayout(app.UIFigure);
            app.GridLayout.ColumnWidth = {281, '1x'};
            app.GridLayout.RowHeight = {'1x'};
            app.GridLayout.ColumnSpacing = 0;
            app.GridLayout.RowSpacing = 0;
            app.GridLayout.Padding = [0 0 0 0];
            app.GridLayout.Scrollable = 'on';

            % Create LeftPanel
            app.LeftPanel = uipanel(app.GridLayout);
            app.LeftPanel.TitlePosition = 'centertop';
            app.LeftPanel.Title = 'Control';
            app.LeftPanel.Layout.Row = 1;
            app.LeftPanel.Layout.Column = 1;

            % Create ConnectButton
            app.ConnectButton = uibutton(app.LeftPanel, 'push');
            app.ConnectButton.ButtonPushedFcn = createCallbackFcn(app, @ConnectButtonPushed, true);
            app.ConnectButton.BackgroundColor = [1 0 0];
            app.ConnectButton.Position = [95 617 118 40];
            app.ConnectButton.Text = 'Connect';

            % Create CommandeButtonGroup
            app.CommandeButtonGroup = uibuttongroup(app.LeftPanel);
            app.CommandeButtonGroup.SelectionChangedFcn = createCallbackFcn(app, @CommandeButtonGroupSelectionChanged, true);
            app.CommandeButtonGroup.Title = 'Commande';
            app.CommandeButtonGroup.Position = [15 481 164 126];

            % Create OffButton
            app.OffButton = uiradiobutton(app.CommandeButtonGroup);
            app.OffButton.Text = 'Off';
            app.OffButton.Position = [11 82 58 22];
            app.OffButton.Value = true;

            % Create StepButton
            app.StepButton = uiradiobutton(app.CommandeButtonGroup);
            app.StepButton.Text = 'Step';
            app.StepButton.Position = [11 40 65 22];

            % Create ClosedLoopButton
            app.ClosedLoopButton = uiradiobutton(app.CommandeButtonGroup);
            app.ClosedLoopButton.Text = 'ClosedLoop';
            app.ClosedLoopButton.Position = [11 19 86 22];

            % Create OpenLoopButton
            app.OpenLoopButton = uiradiobutton(app.CommandeButtonGroup);
            app.OpenLoopButton.Text = 'OpenLoop';
            app.OpenLoopButton.Position = [11 61 78 22];

            % Create SENDButton
            app.SENDButton = uibutton(app.LeftPanel, 'push');
            app.SENDButton.ButtonPushedFcn = createCallbackFcn(app, @SENDButtonPushed, true);
            app.SENDButton.Position = [15 352 122 53];
            app.SENDButton.Text = 'SEND';

            % Create CmdEditFieldLabel
            app.CmdEditFieldLabel = uilabel(app.LeftPanel);
            app.CmdEditFieldLabel.HorizontalAlignment = 'right';
            app.CmdEditFieldLabel.Position = [157 368 31 22];
            app.CmdEditFieldLabel.Text = 'Cmd';

            % Create CmdEditField
            app.CmdEditField = uieditfield(app.LeftPanel, 'numeric');
            app.CmdEditField.Position = [194 356 45 45];

            % Create SaveDataButton
            app.SaveDataButton = uibutton(app.LeftPanel, 'push');
            app.SaveDataButton.ButtonPushedFcn = createCallbackFcn(app, @SaveDataButtonPushed, true);
            app.SaveDataButton.Position = [15 216 100 22];
            app.SaveDataButton.Text = 'SaveData';

            % Create PlotterLabel
            app.PlotterLabel = uilabel(app.LeftPanel);
            app.PlotterLabel.Position = [20 237 40 22];
            app.PlotterLabel.Text = 'Plotter';

            % Create Image
            app.Image = uiimage(app.LeftPanel);
            app.Image.Position = [15 7 249 105];
            app.Image.ImageSource = 'logo.png';

            % Create ClearDataButton
            app.ClearDataButton = uibutton(app.LeftPanel, 'push');
            app.ClearDataButton.ButtonPushedFcn = createCallbackFcn(app, @ClearDataButtonPushed, true);
            app.ClearDataButton.Position = [164 216 100 22];
            app.ClearDataButton.Text = 'ClearData';

            % Create Ref0EditFieldLabel
            app.Ref0EditFieldLabel = uilabel(app.LeftPanel);
            app.Ref0EditFieldLabel.HorizontalAlignment = 'right';
            app.Ref0EditFieldLabel.Position = [9 432 31 22];
            app.Ref0EditFieldLabel.Text = 'Ref0';

            % Create Ref0EditField
            app.Ref0EditField = uieditfield(app.LeftPanel, 'numeric');
            app.Ref0EditField.ValueChangedFcn = createCallbackFcn(app, @Ref0EditFieldValueChanged, true);
            app.Ref0EditField.Position = [46 420 45 45];

            % Create Ref1EditFieldLabel
            app.Ref1EditFieldLabel = uilabel(app.LeftPanel);
            app.Ref1EditFieldLabel.HorizontalAlignment = 'right';
            app.Ref1EditFieldLabel.Position = [101 431 31 22];
            app.Ref1EditFieldLabel.Text = 'Ref1';

            % Create Ref1EditField
            app.Ref1EditField = uieditfield(app.LeftPanel, 'numeric');
            app.Ref1EditField.ValueChangedFcn = createCallbackFcn(app, @Ref1EditFieldValueChanged, true);
            app.Ref1EditField.Position = [138 419 45 45];

            % Create Ref2EditFieldLabel
            app.Ref2EditFieldLabel = uilabel(app.LeftPanel);
            app.Ref2EditFieldLabel.HorizontalAlignment = 'right';
            app.Ref2EditFieldLabel.Position = [187 431 31 22];
            app.Ref2EditFieldLabel.Text = 'Ref2';

            % Create Ref2EditField
            app.Ref2EditField = uieditfield(app.LeftPanel, 'numeric');
            app.Ref2EditField.ValueChangedFcn = createCallbackFcn(app, @Ref2EditFieldValueChanged, true);
            app.Ref2EditField.Position = [224 419 45 45];

            % Create RobotIPEditFieldLabel
            app.RobotIPEditFieldLabel = uilabel(app.LeftPanel);
            app.RobotIPEditFieldLabel.HorizontalAlignment = 'right';
            app.RobotIPEditFieldLabel.Position = [29 665 52 22];
            app.RobotIPEditFieldLabel.Text = 'Robot IP';

            % Create RobotIPEditField
            app.RobotIPEditField = uieditfield(app.LeftPanel, 'text');
            app.RobotIPEditField.Position = [96 665 100 22];

            % Create RightPanel
            app.RightPanel = uipanel(app.GridLayout);
            app.RightPanel.TitlePosition = 'centertop';
            app.RightPanel.Title = 'Measurements';
            app.RightPanel.Layout.Row = 1;
            app.RightPanel.Layout.Column = 2;

            % Create UIAxes_data1
            app.UIAxes_data1 = uiaxes(app.RightPanel);
            title(app.UIAxes_data1, 'Data0')
            xlabel(app.UIAxes_data1, 'second')
            ylabel(app.UIAxes_data1, 'Y')
            zlabel(app.UIAxes_data1, 'Z')
            app.UIAxes_data1.XGrid = 'on';
            app.UIAxes_data1.YGrid = 'on';
            app.UIAxes_data1.Position = [11 481 536 197];

            % Create UIAxes_data2
            app.UIAxes_data2 = uiaxes(app.RightPanel);
            title(app.UIAxes_data2, 'Data1')
            xlabel(app.UIAxes_data2, 'second')
            ylabel(app.UIAxes_data2, 'Y')
            zlabel(app.UIAxes_data2, 'Z')
            app.UIAxes_data2.XGrid = 'on';
            app.UIAxes_data2.YGrid = 'on';
            app.UIAxes_data2.Position = [11 250 536 197];

            % Create UIAxes_data3
            app.UIAxes_data3 = uiaxes(app.RightPanel);
            title(app.UIAxes_data3, 'Data2')
            xlabel(app.UIAxes_data3, 'second')
            ylabel(app.UIAxes_data3, 'Y')
            zlabel(app.UIAxes_data3, 'Z')
            app.UIAxes_data3.XGrid = 'on';
            app.UIAxes_data3.YGrid = 'on';
            app.UIAxes_data3.Position = [11 31 536 197];

            % Show the figure after all components are created
            app.UIFigure.Visible = 'on';
        end
    end

    % App creation and deletion
    methods (Access = public)

        % Construct app
        function app = ESP32App

            % Create UIFigure and components
            createComponents(app)

            % Register the app with App Designer
            registerApp(app, app.UIFigure)

            % Execute the startup function
            runStartupFcn(app, @StartUp)

            if nargout == 0
                clear app
            end
        end

        % Code that executes before app deletion
        function delete(app)

            % Delete UIFigure when app is deleted
            delete(app.UIFigure)
        end
    end
end