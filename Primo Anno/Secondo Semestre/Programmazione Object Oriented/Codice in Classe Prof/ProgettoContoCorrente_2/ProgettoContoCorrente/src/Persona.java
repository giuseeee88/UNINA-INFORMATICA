
public class Persona {
	
	private String Nome;
	private String Cognome;
	private String CodiceFiscale;
	
	
	public Persona(String newNome, String newCognome, String newCF) {
		Nome = newNome;
		Cognome = newCognome;
		CodiceFiscale = newCF;
	}
	
	public String getNome() {
		return Nome;
	}

	
	public String getCognome() {
		return Cognome;
	}
	
	public String getCodiceFiscale() {
		return CodiceFiscale;
	}
	
	public String dettaglioPersona() {
		return "Nome: "+Nome+", Cognome: "+Cognome+", CF: "+CodiceFiscale;
	}
}
