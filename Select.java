import java.util.Map;

public class Select implements Command {
  private boolean selected;
  
  private String selection;
  
  public void execute(String param1, Map<String, DinoszauruszonLovagloGepfegyveresAmazon> param2, Select command) {
    if (param2.containsKey(param1)) {
      this.selection = param1;
      this.selected = true;
      System.out.println(param1 + " kiválasztva.");
    } else {
      this.selected = false;
      System.out.println("nincs ilyen amazon");
    } 
  }
  
  public boolean execute() {
    return true;
  }
  
  public String getSelection() {
    return this.selection;
  }
  
  public boolean isSelected() {
    return this.selected;
  }
}
