classdef Frame
   properties
      Mark uint8
      Id uint8
      Cmd uint8
      data1 int32
      data2 int32
      data3 int32
      CheckSum uint8
   end
   methods
       function r = calc_checksum(obj)
           r = uint8(mod(sum([obj.Mark obj.Id obj.Cmd typecast(obj.data1,'uint8') typecast(obj.data2,'uint8') typecast(obj.data3,'uint8')]),256));
       end
     function r = formatframe(obj)
           r = [obj.Mark obj.Id obj.Cmd typecast(obj.data1,'uint8') typecast(obj.data2,'uint8') typecast(obj.data3,'uint8') obj.calc_checksum()];
     end
     function obj=recevframe(obj,data) 
        obj.Mark = data(1);
        obj.Id = data(2);
        obj.data1 = typecast(data(4:7),'int32');
     end
    end
end