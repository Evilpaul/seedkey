using skwrapper;
using System;

namespace test
{
    internal class Program
    {
        static void Main(string[] args)
        {
            VKeyGenResultExOpt retVal;
            uint oActualKeyArraySize;
            uint iSecurityLevel = 1;
            string ipVariant = string.Empty;
            string ipOptions = "01234567890123456";
            byte[] iopKeyArray = new byte[32];
            byte[] ipSeedArray = new byte[16] { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

            seedkey_wrapper skw = new seedkey_wrapper();

            Console.WriteLine($"Calling {nameof(skw.GenerateKeyExOpt)}");
            Console.Write("Seed   : ");
            foreach (byte element in ipSeedArray)
            {
                Console.Write($"{element:X2} ");
            }
            Console.WriteLine();

            retVal = skw.GenerateKeyExOpt(ipSeedArray, iSecurityLevel, ipVariant, ipOptions, out iopKeyArray, out oActualKeyArraySize);

            Console.WriteLine($"Result : {retVal}");
            // only output other parameter details if the result was OK
            if (retVal == VKeyGenResultExOpt.KGREO_Ok)
            {
                Console.Write("Key    : ");
                for (int i = 0; i < oActualKeyArraySize; i++)
                {
                    Console.Write($"{iopKeyArray[i]:X2} ");
                }
                Console.WriteLine();
            }
        }
    }
}
