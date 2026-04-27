
public class Persona {
	
	private String Nome;
	private String Cognome;
	private String CodiceFiscale;
	private ContoCorrente[] ElencoConti;
	private int numeroConti=0;
	
	
	public Persona(String newNome, String newCognome, String newCF) {
		Nome = newNome;
		Cognome = newCognome;
		CodiceFiscale = newCF;
		ElencoConti = new ContoCorrente[5];
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
	
	
	public boolean addConto(ContoCorrente newConto) {
		
		for(int i=0; i<ElencoConti.length;i++) {
			if (ElencoConti[i]==null) {
				ElencoConti[i]= newConto;
				return true;
			}
		}
		return false;
		
	}
	
//	public ContoCorrente getMioConto() {
//		return mioConto;
//	}
//	
//	
//	public void setMioConto(ContoCorrente newConto) {
//		mioConto=newConto;
//		
//	}
	
	
	public String dettaglioPersona() {
		return "Nome: "+Nome+", Cognome: "+Cognome+", CF: "+CodiceFiscale;
	}
}
