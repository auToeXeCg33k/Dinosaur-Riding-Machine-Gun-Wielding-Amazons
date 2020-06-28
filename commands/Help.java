package commands;

import core.World;

public class Help implements Command {
  public void execute(String[] strs, World world) {
    System.out.println("A játék 2 játékossal játszható.");
    System.out.println("Mindkét játékos amazonokat hozhat létre és irányíthat, amelyek lovagolhatnak dinoszauruszokon, tárgyakat vehetnek fel, és ezek segítségével a szart is kiölhetik egymásból.");
    System.out.println("A játék világa csempékböl áll, ezekre koordinátákkal lehet hivatkozni.");
    System.out.println("A játék körökben játszható.");
    System.out.println("Játékmódtól függöen korlátozva van, hogy egy játékos összesen hány amazont hozhat létre, egyszerre hány élö amazonja lehet a pályán, és hány lépést tehet egy-egy körben.");
    System.out.println("A cél az ellenfél összes lehetséges amazonját elpusztítani.");
    System.out.println("Az gyöz, aki nem veszít.");
    System.out.println("A játékban minden tevékenység parancsokkal végezhető.\nAz elérhetö parancsok az alábbiak:");
    System.out.println("exit: most magyarázzam?");
    System.out.println("new [név]: létrehoz egy amazont a megadott névvel.");
    System.out.println("select [név]: kiválasztja a megadott amazont.");
    System.out.println("attack [név]: a kiválaszott amazon megtámadja a megadott amazont.");
    System.out.println("move [x] [y]: a kiválasztott amazon a megadott koordinátára mozdul.");
    System.out.println("lookaround: a kiválasztott amazon megvizsgálja környezetét.");
    System.out.println("tame: a kiválasztott amazon beidomítja a környezetében lévő dinoszauruszt.");
    System.out.println("geton: a kiválaszott amazon felszáll a dinoszauruszára.");
    System.out.println("getoff: a kiválasztott amazon leszáll a dinoszauruszáról.");
    System.out.println("status: a kiválasztott amazon aktuális adatai.");
    System.out.println("pickup [itemnév]: a kiválasztott amazon felveszi a megadott tárgyat.");
    System.out.println("drop [itemnév]: a kiválasztott amazon eldobja a megadott tárgyat.");
    System.out.println("equip [fegyvernév]: a kiválasztott amazon kézbe veszi a megadott fegyvert.");
    System.out.println("steps: kiírja az aktuális játékos lehetőségeit, állását.");
    System.out.println("end: a kör befejezése.");
    System.out.println("list: az aktuális játékos összes amazonjának listája.\n");
  }
}
