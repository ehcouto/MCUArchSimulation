using MathWorks.MATLAB.Engine;
using MathWorks.MATLAB.Types;

namespace Speedgoat;

public class Target
{
    dynamic matlab;
    bool isInstrument;
    public Target(string ip_address)
    {
        matlab = MATLABEngine.StartMATLAB();
        matlab.eval(new RunOptions(nargout: 0), @"tg = slrealtime()");
        matlab.eval(new RunOptions(nargout: 0), String.Format(@"tg.TargetSettings.address = '{0}'", ip_address)); // @"tg.TargetSettings.address = '192.168.7.5'"); // Jenkins empty address issue workaround

        isInstrument = false;
    }

    public string GetTargetSettings()
    {
        string res = matlab.eval(@"tg.TargetSettings");
        return res;
    }

    public void Load(string application)
    {
        matlab.eval(new RunOptions(nargout: 0), @"tg.connect()");
        Stop();        
        matlab.eval(new RunOptions(nargout: 0), String.Format(@"tg.load('{0}')", application));
    }

    public void Start(int timeout=100, string reload="true")
    {
        var timer = 0;
        while (GetStatus() != "loaded")
        {
            timer += 1;
            Thread.Sleep(100);
            if (timer >= timeout)
            {
                throw new Exception("Timeout starting the plant (not loaded)!");
            } 
        }
        matlab.eval(new RunOptions(nargout: 0), String.Format(@"tg.start('ReloadOnStop',{0})", reload));
        timer = 0;
        while (GetStatus() != "running")
        {
            timer += 1;
            Thread.Sleep(100);
            if (timer >= timeout)
            {
                throw new Exception("Timeout starting the plant!");
            } 
        }
    }

    public void Stop(int timeout=100)
    {
        var timer = 0;
        matlab.eval(new RunOptions(nargout: 0), @"tg.stop");
        while ((GetStatus() == "running"))
        {
            timer += 1;
            Thread.Sleep(100);
            if (timer >= timeout)
            {
                throw new Exception("Timeout stopping the plant!");                
            } 
        }
    }

    public string GetStatus()
    {
        string res = matlab.eval(@"tg.status");
        return res;
    }

    public void SetParam(string blkpath, string param, double value)
    {
        matlab.eval(new RunOptions(nargout: 0), String.Format(@"tg.setparam('{0}','{1}',{2})",blkpath, param, value));
    }

    public double GetParam(string blkpath, string param)
    {
        double value = matlab.eval(new RunOptions(nargout: 1), String.Format(@"tg.getparam('{0}','{1}')",blkpath, param));
        return value;
    }

    public void SetBoolParam(string blkpath, string param, bool value)
    {
        matlab.eval(new RunOptions(nargout: 0), String.Format(@"tg.setparam('{0}','{1}',{2})",blkpath, param, value.ToString().ToLower()));
    }

    /// <summary>
    /// Overwrites a model quantity
    /// </summary>
    /// <remarks>
    /// This method makes assumption on the naming conventions in the model 
    /// </remarks>
    /// <param name="path">signal path</param>
    /// <param name="value">desired value</param>
    public void OverwriteQuantity((string, int) path, double value)
    {
        SetParam(path.Item1 + " Value", "Value", value);            
        SetBoolParam(path.Item1 + " Enable", "Value", true);
    }

    public void OverwriteParameter((string, string) path, double value)
    {
        SetParam(path.Item1, path.Item2, value);            
    }

    public double ReadParameter((string, string) path)
    {
        double value = GetParam(path.Item1, path.Item2);   
        return value;         
    }


    public void CaptureSignal(string application, string blkpath, int portnumber)
    {
        if (!isInstrument)
        {
            matlab.eval(new RunOptions(nargout: 0), String.Format(@"instrument = slrealtime.Instrument('{0}')",application));
            isInstrument = true;
        }
        matlab.eval(new RunOptions(nargout: 0), String.Format(@"instrument.addSignal('{0}', {1})",blkpath,portnumber));
        matlab.eval(new RunOptions(nargout: 0), @"tg.addInstrument(instrument)");
    }

    /// <summary>
    /// Get a model signal value
    /// </summary>
    /// <param name="path"></param>
    /// <returns>The value from the running model</returns>
    public double GetSignalValue(ValueTuple<string, int> path)
    {
        double result = matlab.eval(String.Format(@"tg.getsignal('{0}', {1})", path.Item1, path.Item2));
        
        return result;
    }

    public void CloseSession()
    {
        try
        {
            Stop();
        }
        catch { };
        matlab.eval(new RunOptions(nargout: 0), @"tg.disconnect()");
        matlab.eval(new RunOptions(nargout: 0), @"clear mex");
        matlab.eval(new RunOptions(nargout: 0), @"clear all");
        MATLABEngine.TerminateEngineClient();
    }

    public void SaveLogs(string filename)
    {
        matlab.eval(new RunOptions(nargout: 0), $"save('{filename}', 'logsout')");
    }

}
