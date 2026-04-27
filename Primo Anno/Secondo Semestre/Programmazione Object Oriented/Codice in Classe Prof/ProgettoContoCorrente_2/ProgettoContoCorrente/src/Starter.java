
public class Starter {

	public static void main(String[] args) {

		Persona p1 = new Persona("Antonio", "Esposito", "fyguiegy");
		ContoCorrente c1 = new ContoCorrente("IT012345", p1);
		c1.deposita(1000);
		
		
		
		Persona p2 = new Persona("Valeria", "Rossi", "GSDUGYW");
		ContoCorrente c2 = new ContoCorrente("IT987654", p2);
		c2.deposita(4000);
		
		System.out.println(c1.DettagliConto());
		System.out.println(c2.DettagliConto());
	}

}
