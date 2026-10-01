using System.Reflection;
namespace Parcial_lab_software
{
    class Program
    {
        static string GetInput(string mensaje)
        {
            while (true)
            {
                Console.Write(mensaje);
                string validación = Console.ReadLine();
                if (String.IsNullOrEmpty(validación) || String.IsNullOrWhiteSpace(validación))
                {
                    return null;
                }
                else if (double.TryParse(validación, out double valido))
                {
                    return validación;
                }
                else
                {
                    Console.WriteLine("Entrada no válida. Por favor, ingrese un número.");
                    Console.ReadKey();
                }
            }
        }
        static async Task Main(string[] args)
        {
            Console.Clear();
            List<Ecuaciones> historial = new List<Ecuaciones>();
            bool salir = false;
            while (!salir)
            {
                Console.WriteLine("Calcular Ecuaciones Cuadraticas");
                Console.WriteLine("\n1. Resolver Ecuación Cuadratica\n2. Historial\n3. Salir");
                Console.Write("\nSeleccione una opción: ");
                if (!int.TryParse(Console.ReadLine(), out int opcion))
                {
                    Console.WriteLine("Entrada no válida. Por favor, ingrese un número.");
                    Console.ReadKey();
                    Console.Clear();
                }
                else
                {
                    switch (opcion)
                    {
                        case 1:
                            string a = GetInput("\nIngrese coeficiente A: ");
                            string b = GetInput("\nIngrese coeficiente B: ");
                            string c = GetInput("\nIngrese coeficiente C (Dejar vacio para ecuación lineal): ");

                            Ecuaciones ecuacion = new Ecuaciones();
                            ecuacion.Calcular(a, b, c);
                            historial.Add(ecuacion);

                            Console.ReadKey();
                            Console.Clear();
                            break;
                        case 2:
                            if (historial.Count == 0)
                            {
                                Console.WriteLine("No hay historial de ecuaciones.");
                            }
                            else
                            {
                                for (int i = 0; i < historial.Count; i++)
                                {
                                    if (historial[i].Discriminante == false && historial[i].A.HasValue && historial[i].C.HasValue)
                                    {
                                        Console.WriteLine($"Ecuación {i + 1}: A = {historial[i].A}, B = {historial[i].B}, C = {historial[i].C}. Raices Complejas.");
                                    }
                                    else if (historial[i].A.HasValue && historial[i].C.HasValue)
                                    {
                                        Console.WriteLine($"Ecuación {i + 1}: A = {historial[i].A}, B = {historial[i].B}, C = {historial[i].C}. Raices: x1 = {historial[i].x1}, x2 = {historial[i].x2}");
                                    }
                                    else if (historial[i].A == 0 || historial[i].A == null || historial[i].C == null)
                                    {
                                        Console.WriteLine($"Ecuación {i + 1}: A = {historial[i].A}, B = {historial[i].B}. Raices: x = {-historial[i].B / historial[i].A}");
                                    }
                                }
                            }
                            Console.ReadKey();
                            Console.Clear();
                            break;
                        case 3:
                            Console.WriteLine("Gracias, ¡vuelva pronto!");
                            await Task.Delay(650);
                            salir = true;
                            break;
                        default:
                            Console.WriteLine("Opción no válida. Por favor, elija una opción del menú.");
                            Console.ReadKey();
                            Console.Clear();
                            break;
                    }
                }
            }
        }
        public class Ecuaciones
        {
            public double? A { get; set; }
            public double B { get; set; }
            public double? C { get; set; }
            public double x1 { get; set; }
            public double x2 { get; set; }
            public bool Discriminante { get; private set; }
            public void Calcular(string? a, string b, string? c)
            {
                A = a != null ? double.Parse(a) : null;
                B = double.Parse(b);
                C = c != null ? double.Parse(c) : null;
                if (A == 0 && B == 0)
                {
                    Console.WriteLine($"A = {A}, B = {B}. Raiz simple: {C}");
                }
                else if (A == null || A == 0 || C == null)
                {
                    if (A == null || A == 0)
                    {
                        A = double.Parse(b);
                        B = double.Parse(c);
                        C = null;
                    }
                    Console.WriteLine($"\nLa ecuación es lineal: A = {A}, B = {B}. Raices: x = {-B / A}");
                }
                else if (A.HasValue && C.HasValue && A != 0 && B != 0)
                {
                    double discriminante = Math.Pow(B, 2) - 4 * A.Value * C.Value;
                    Discriminante = discriminante >= 0;
                    if (discriminante >= 0)
                    {
                        double sqrtDiscriminante = Math.Sqrt(discriminante);
                        x1 = (B + sqrtDiscriminante) / (2 * A.Value);
                        x2 = (B - sqrtDiscriminante) / (2 * A.Value);
                        Console.WriteLine($"Ecuación Cuadrática: A = {A}, B = {B}, C = {C}. Raices: x1 = {x1}, x2 = {x2}");
                    }
                    else
                    {
                        Console.WriteLine($"Ecuación Cuadrática: A = {A}, B = {B}, C = {C}. Raices Complejas.");
                    }
                }
            }
        }
    }
}