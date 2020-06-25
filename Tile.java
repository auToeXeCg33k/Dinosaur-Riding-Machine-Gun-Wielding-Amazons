import java.util.ArrayList;

public class Tile {
  private ArrayList<Amazon> amazonList = new ArrayList<>();
  
  private ArrayList<Dinoszaurusz> dinoszauruszList = new ArrayList<>();
  
  public void addAmazon(Amazon a) {
    this.amazonList.add(a);
  }
  
  public void addDinoszaurusz(Dinoszaurusz d) {
    this.dinoszauruszList.add(d);
  }
  
  public boolean containsDinoszaurusz(Dinoszaurusz d) {
    return this.dinoszauruszList.contains(d);
  }
  
  public boolean containsAmazon(Amazon a) {
    return this.amazonList.contains(a);
  }
}
