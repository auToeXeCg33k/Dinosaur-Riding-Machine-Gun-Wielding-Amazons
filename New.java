import java.util.Map;

public class New implements Command {
  public void execute(String param1, Map<String, DinoszauruszonLovagloGepfegyveresAmazon> param2, Select command) {
    if (param2.containsKey(param1)) {
      System.out.println("ilyen mán van");
    } else {
      param2.put(param1, new DinoszauruszonLovagloGepfegyveresAmazon(param1, true, true, true));
      System.out.println(param1 + " létrehozva");
    } 
  }
  
  public boolean execute() {
    return true;
  }
}
