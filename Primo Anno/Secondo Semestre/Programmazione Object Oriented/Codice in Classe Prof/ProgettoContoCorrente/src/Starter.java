
public class Starter {

	public static void main(String[] args) {

		ContoCorrente c1 = new ContoCorrente("IT012345", "Topolino");
		c1.deposita(1000);
		
		ContoCorrente c2 = new ContoCorrente("IT987654", "Pippo");
		c2.deposita(4000);
		
		System.out.println(c1.DettagliConto());
		System.out.println(c2.DettagliConto());
	}

}
