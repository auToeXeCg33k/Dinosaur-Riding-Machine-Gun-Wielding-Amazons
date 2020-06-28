class Help implements Command {
  public void execute(String[] strs, World world) {}
  
  public boolean execute() {
    System.out.println("A játékban amazonokat irányítasz egy csempealapú világban.");
    System.out.println("Az amazonok lovagolhtnak dinoszauruszokon, tárgyakat vehetnek fel, és ezek segítségével a szart is kiölhetik egymásból.");
    System.out.println("A játékban minden tevékenység parancsokkal végezhető.\nAz elérhető parancsok az alábbiak:");
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
    System.out.println("pickup [itemnév]: a kiválasztott amazon felveszi a megadott tárgyat,");
    System.out.println("drop [itemnév]: a kiválasztott amazon eldobja a megadott tárgyat");
    System.out.println("equip [fegyvernév]: a kiválasztott amazon kézbe veszi a megadott fegyvert");
    return true;
  }
}
