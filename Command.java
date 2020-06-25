import java.util.Map;

public interface Command {
  void execute(String paramString, Map<String, DinoszauruszonLovagloGepfegyveresAmazon> paramMap, Select paramSelect);
  
  boolean execute();
}
