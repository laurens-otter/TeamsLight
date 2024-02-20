using System;
using System.IO;
using System.IO.Ports;
using System.Collections.Generic;
using System.Management;
using System.Text.RegularExpressions;

class Program
{
    static void Main()
    {
        // Define the file path in the user's AppData folder
        string appDataFolder = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
        string filePath = Path.Combine(appDataFolder,"Microsoft","Teams","logs.txt");

        // Let windows return usb devices and search for Serial device
        string comPort = GetComPortForSerialDevice();        

        // Set up serial port
        SerialPort serialPort = new SerialPort(comPort);
        serialPort.BaudRate = 9600;

        // Ensure the serial port is closed when the program exits
        AppDomain.CurrentDomain.ProcessExit += (sender, e) => {
            if (serialPort.IsOpen)
                SendSerialCommand(comPort, 9600, "off");
                serialPort.Close();
        };
        // Continuously monitor the file
        while (true)
        {
            // Check if the file exists
            if (File.Exists(filePath))
            {       
                 // Attempt to open the log file with read access and allow other processes to read/write
                using (FileStream fileStream = new FileStream(filePath, FileMode.Open, FileAccess.Read, FileShare.ReadWrite))
                {            
                    // Wrap the FileStream in a StreamReader for easier reading
                    using (StreamReader reader = new StreamReader(fileStream))
                    {
                        // Read all lines from the file
                        string lastLineWithStatus = null;
                        string line;
                        // Look for the line containing "StatusIndicatorState"
                        while ((line = reader.ReadLine()) != null)
                        {   
                            if (line.Contains("StatusIndicatorStateService: Added"))
                            {
                                lastLineWithStatus = line;
                            }
                        }
                        if (lastLineWithStatus != null)
                        {
                            // Use regular expression to extract the word after "StatusIndicatorState"
                            Match match = Regex.Match(lastLineWithStatus, @"StatusIndicatorStateService: Added\s+(\w+)");
                            if (match.Success)
                            {
                                string status = match.Groups[1].Value;                         
                                // Check if the value matches a certain condition
                                if (status == "Busy" || status == "OnThePhone")
                                    {
                                        // Send serial command to COM port 6
                                        SendSerialCommand(comPort, 9600, "red");
                                    }
                                if (status == "Available")
                                    {
                                        // Send serial command to COM port 6
                                        SendSerialCommand(comPort, 9600, "green");
                                    }
                                if (status == "Away")
                                    {
                                        // Send serial command to COM port 6
                                        SendSerialCommand(comPort, 9600, "yellow");
                                    }
                            }
                            else
                            {
                                SendSerialCommand(comPort, 9600, "off");
                            }
                        }
                    }
                }
            }
            // Sleep for a while before checking the file again
            System.Threading.Thread.Sleep(2000);
        }
    }
    static void SendSerialCommand(string portName, int baudRate, string command)
    {
        using (SerialPort serialPort = new SerialPort(portName, baudRate))
        {
            try
            {
                serialPort.Open();
                serialPort.Write(command);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error sending serial command: " + ex.Message);
            }
        }
    }
    static string GetComPortForSerialDevice()
    {
        ManagementObjectSearcher searcher =
            new ManagementObjectSearcher("SELECT * FROM Win32_PnPEntity WHERE Caption LIKE '%(COM%'");

        foreach (ManagementObject queryObj in searcher.Get())
        {
            string caption = queryObj["Caption"].ToString();
            if (caption.Contains("(COM"))
            {
                if (caption.Contains("USB Serial Device"))
                {
                    int startIndex = caption.LastIndexOf("(COM") + 1;
                    int endIndex = caption.LastIndexOf(")");
                    return caption.Substring(startIndex, endIndex - startIndex);
                }
            }
        }

        return "Serial device not found or COM port not available";
    }
}
