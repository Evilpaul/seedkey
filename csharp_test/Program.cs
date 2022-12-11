using skwrapper;
using System;

namespace csharp_test
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
            byte[] ipSeedArray = new byte[16];

            seedkeywrapper skw = new seedkeywrapper();

            Console.WriteLine($"Calling {nameof(skw.GenerateKeyExOpt)}");
            retVal = skw.GenerateKeyExOpt(ipSeedArray, iSecurityLevel, ipVariant, ipOptions, out iopKeyArray, out oActualKeyArraySize);
            Console.WriteLine($"{retVal}");
            foreach (int element in iopKeyArray)
            {
                Console.Write($"{element:X2} ");
            }
            Console.WriteLine();
            Console.WriteLine($"{oActualKeyArraySize}");
        }
    }
}
