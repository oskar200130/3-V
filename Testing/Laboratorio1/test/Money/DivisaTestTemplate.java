package Money;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import Money.Divisa;

public class DivisaTestTemplate {
	Divisa SEK, DKK, NOK, EUR;
	
	@Before
	public void setUp() throws Exception {
		SEK = new Divisa("SEK", 0.15);
		DKK = new Divisa("DKK", 0.20);
		EUR = new Divisa("EUR", 1.5);
	}

	@Test
	public void testGetName() {
		assertEquals("SEK no tiene el nombre correspondiente", "SEK", SEK.getName());
		assertEquals("DKK no tiene el nombre correspondiente", "DKK", DKK.getName());
		assertEquals("EUR no tiene el nombre correspondiente", "EUR", EUR.getName());
	}
	
	@Test
	public void testGetRate() {
		assertTrue("SEK no tiene el nombre correspondiente", 0.15 == SEK.getRate());
		assertTrue("DKK no tiene el nombre correspondiente", 0.2 == DKK.getRate());
		assertTrue("EUR no tiene el nombre correspondiente", 1.5 == EUR.getRate());
	}
	
	@Test
	public void testSetRate() {
		SEK.setRate(2.4);
		assertTrue("Setrate no cambia bien el rate", SEK.getRate()==2.4);
	}
	
	@Test
	public void testGlobalValue() {
		fail("No implementado");
	}
	
	@Test
	public void testValueEnEstaDivisa() {
		fail("No implementado");
	}

}
