
public class ContoCorrente {
	
	String IBAN;
	Persona Intestatario;
	private double Saldo;
	
	public ContoCorrente(String newIBAN, Persona newIntestatario) {
		IBAN=newIBAN;
		Intestatario = newIntestatario;
		Saldo=0.5;
	}
	
	
	public boolean deposita(double amount) {
		if (amount>0) {
			Saldo+=amount;
			return true;
		}
		else
			return false;
		
	}
	
	public boolean preleva(double amount) {
		if(amount>0 && Saldo-amount>=0) {
			Saldo-=amount;
			return true;
		}
		else
			return false;
		
	}
	
	public String DettagliConto() {
		return "Il conto "+IBAN+ " di "+ Intestatario.dettaglioPersona()+" ha "+Saldo+"€";
		
		
	}

}
