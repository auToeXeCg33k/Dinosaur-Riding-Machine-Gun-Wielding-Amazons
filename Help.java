import java.util.Map;

class Help implements Command {
  public void execute(String param1, Map<String, DinoszauruszonLovagloGepfegyveresAmazon> param2, Select command) {}
  
  public boolean execute() {
    System.out.println("na, ezeket írhatod be");
    System.out.println("exit: most magyarázzam?");
    System.out.println("new [név]: csinál egy amazont azzal a névvel amit beírsz");
    System.out.println("select [név]: kiválaszt egy amazont azzal a névvel amit beírsz");
    System.out.println("attack [név]: a kiválaszott amazon megtámadja a megadott amazont");
    return true;
  }
}
