class Help implements Command {
  public void execute(String[] strs, World world) {}
  
  public boolean execute() {
    System.out.println("A játékban kétféle entitás létezik : dinoszaurusz és amazon. Ezek képesek támadni, mozogni, vizsgálódni.");
    System.out.println("Az elérhető parancsok az alábbiak:");
    System.out.println("exit: most magyarázzam?");
    System.out.println("new [entitástípus] [név]: csinál egy entitást azzal a névvel és típussal, amit beírsz");
    System.out.println("select [entitástípus] [név]: kiválaszt egy entitást azzal a névvel és típussal, amit beírsz");
    System.out.println("attack [név]: a kiválaszott amazon megtámadja a megadott amazont");
    System.out.println("where: a kiválasztott entitás tartózkodási helye");
    System.out.println("move [x] [y]: a kiválasztott entitás a megadott koordinátára mozdul");
    return true;
  }
}
