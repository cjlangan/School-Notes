/*
THIS IS A GENERATED/BUNDLED FILE BY ESBUILD
if you want to view the source, please visit the github repository of this plugin
*/

var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __export = (target, all) => {
  for (var name in all)
    __defProp(target, name, { get: all[name], enumerable: true });
};
var __copyProps = (to, from, except, desc) => {
  if (from && typeof from === "object" || typeof from === "function") {
    for (let key of __getOwnPropNames(from))
      if (!__hasOwnProp.call(to, key) && key !== except)
        __defProp(to, key, { get: () => from[key], enumerable: !(desc = __getOwnPropDesc(from, key)) || desc.enumerable });
  }
  return to;
};
var __toCommonJS = (mod) => __copyProps(__defProp({}, "__esModule", { value: true }), mod);

// src/main.ts
var main_exports = {};
__export(main_exports, {
  default: () => HtmlLocalSrcPlugin
});
module.exports = __toCommonJS(main_exports);
var import_obsidian = require("obsidian");
var HtmlLocalSrcPlugin = class extends import_obsidian.Plugin {
  constructor() {
    super(...arguments);
    this.enableLog = false;
    this.log = this.enableLog ? console.log : () => {
    };
    /*
    scroll 子函数
     */
    this.scrollLines = async (element) => {
      let rect = element.getBoundingClientRect();
      const height = rect.height;
      const clientHeight = Math.round(element.clientHeight);
      const scrollTop = Math.round(element.scrollTop);
      const lineHeight = height / clientHeight;
      const scrollLines = Math.round(scrollTop / lineHeight);
      this.log("scrollHeight ", scrollTop % clientHeight - clientHeight / 4 < 0);
      if (scrollTop % clientHeight - clientHeight / 4 < 0) {
        this.log("in Scroll");
        this.useProcessMarkdown();
      }
      this.log("You scrollTop " + scrollTop + "  ,Height =" + clientHeight + ", clientHeight " + clientHeight + " lines.");
      return scrollLines;
    };
  }
  onload() {
    this.registerMarkdownPostProcessor((element, ctx) => {
      this.processMarkdown(element);
    });
    this.processView();
    this.registerMarkdownPostProcessor(this.modifyHTML.bind(this));
    this.registerEvent(this.app.workspace.on("file-open", this.processView.bind(this)));
    this.registerEvent(this.app.workspace.on("editor-change", this.useProcessMarkdown.bind(this)));
  }
  /*
  主要函数
   */
  processView() {
    const activeView = this.app.workspace.getActiveViewOfType(import_obsidian.MarkdownView);
    const file = activeView == null ? void 0 : activeView.file;
    if (file == null)
      return;
    this.log("\u6587\u4EF6\u5DF2\u6253\u5F00", file.path);
    this.useProcessMarkdown();
    if (activeView instanceof import_obsidian.MarkdownView) {
      this.scroll_toUpdateView(activeView);
    }
    this.log(import_obsidian.editorLivePreviewField);
    this.log("end");
  }
  processMarkdown(element) {
    const activeView = this.app.workspace.getActiveViewOfType(import_obsidian.MarkdownView);
    const activeFile = activeView == null ? void 0 : activeView.file;
    if (activeFile) {
      const targetLinks = Array.from(element.getElementsByTagName("img")).filter(
        (link) => {
          return link.src.lastIndexOf(":") === 3;
        }
      );
      let activePath = this.app.vault.getResourcePath(activeFile);
      this.log(activeView == null ? void 0 : activeView.getEphemeralState());
      this.log(this.app.workspace);
      this.log(activePath);
      activePath = activePath ? activePath.substring(0, activePath.lastIndexOf("/")) : "";
      for (const link of targetLinks) {
        let cleanLink = link.src.replace("app://obsidian.md/", "");
        link.src = activePath + "/" + cleanLink;
      }
    }
  }
  useProcessMarkdown() {
    const activeView = this.app.workspace.getActiveViewOfType(import_obsidian.MarkdownView);
    this.log("activeView  ", activeView);
    const element = activeView == null ? void 0 : activeView.contentEl;
    if (element) {
      this.processMarkdown(element);
    }
  }
  modifyHTML(el, ctx) {
    this.log("Markdown rendering completed:", ctx.sourcePath);
  }
  scroll_toUpdateView(activeView) {
    let div = activeView.containerEl.querySelector(".cm-scroller");
    this.log(div);
    this.registerDomEvent(div, "scroll", (event) => {
      this.scrollLines(div);
      this.log("Editor Scrolled:   pixels vertically and pixels horizontally.");
    });
  }
};
//# sourceMappingURL=data:application/json;base64,ewogICJ2ZXJzaW9uIjogMywKICAic291cmNlcyI6IFsic3JjL21haW4udHMiXSwKICAic291cmNlc0NvbnRlbnQiOiBbImltcG9ydCB7ZWRpdG9yTGl2ZVByZXZpZXdGaWVsZCwgTWFya2Rvd25WaWV3LCBQbHVnaW4sfSBmcm9tIFwib2JzaWRpYW5cIjtcblxuZXhwb3J0IGRlZmF1bHQgY2xhc3MgSHRtbExvY2FsU3JjUGx1Z2luIGV4dGVuZHMgUGx1Z2luIHtcblx0cHJpdmF0ZSBlbmFibGVMb2cgPSBmYWxzZTtcblx0cHJpdmF0ZSBsb2cgPSB0aGlzLmVuYWJsZUxvZyA/IGNvbnNvbGUubG9nIDogKCkgPT4ge1xuXHR9O1xuXG5cdG9ubG9hZCgpIHtcblx0XHR0aGlzLnJlZ2lzdGVyTWFya2Rvd25Qb3N0UHJvY2Vzc29yKChlbGVtZW50LCBjdHgpID0+IHtcblx0XHRcdHRoaXMucHJvY2Vzc01hcmtkb3duKGVsZW1lbnQpO1xuXHRcdH0pO1xuXHRcdHRoaXMucHJvY2Vzc1ZpZXcoKTsvL2luaXQgY3VycmVudCB2aWV3XG5cdFx0dGhpcy5yZWdpc3Rlck1hcmtkb3duUG9zdFByb2Nlc3Nvcih0aGlzLm1vZGlmeUhUTUwuYmluZCh0aGlzKSk7XG5cdFx0dGhpcy5yZWdpc3RlckV2ZW50KHRoaXMuYXBwLndvcmtzcGFjZS5vbihcImZpbGUtb3BlblwiLCB0aGlzLnByb2Nlc3NWaWV3LmJpbmQodGhpcykpKTtcblx0XHR0aGlzLnJlZ2lzdGVyRXZlbnQodGhpcy5hcHAud29ya3NwYWNlLm9uKFwiZWRpdG9yLWNoYW5nZVwiLHRoaXMudXNlUHJvY2Vzc01hcmtkb3duLmJpbmQodGhpcykpKTtcblx0fVxuXHQvKlxuXHRcdTRFM0JcdTg5ODFcdTUxRkRcdTY1NzBcblx0ICovXG5cdHByb2Nlc3NWaWV3KCkge1xuXHRcdGNvbnN0IGFjdGl2ZVZpZXcgPSB0aGlzLmFwcC53b3Jrc3BhY2UuZ2V0QWN0aXZlVmlld09mVHlwZShNYXJrZG93blZpZXcpO1xuXHRcdGNvbnN0IGZpbGUgPSBhY3RpdmVWaWV3Py5maWxlO1xuXHRcdGlmIChmaWxlID09IG51bGwpIHJldHVybjtcblx0XHR0aGlzLmxvZygnXHU2NTg3XHU0RUY2XHU1REYyXHU2MjUzXHU1RjAwJywgZmlsZS5wYXRoKTtcblx0XHR0aGlzLnVzZVByb2Nlc3NNYXJrZG93bigpO1xuXHRcdGlmIChhY3RpdmVWaWV3IGluc3RhbmNlb2YgTWFya2Rvd25WaWV3KSB7XG5cdFx0XHR0aGlzLnNjcm9sbF90b1VwZGF0ZVZpZXcoYWN0aXZlVmlldyk7XG5cdFx0fVxuXHRcdHRoaXMubG9nKGVkaXRvckxpdmVQcmV2aWV3RmllbGQpXG5cdFx0dGhpcy5sb2coJ2VuZCcpO1xuXHR9XG5cdHByb2Nlc3NNYXJrZG93bihlbGVtZW50OiBIVE1MRWxlbWVudCkge1xuXHRcdGNvbnN0IGFjdGl2ZVZpZXcgPSB0aGlzLmFwcC53b3Jrc3BhY2UuZ2V0QWN0aXZlVmlld09mVHlwZShNYXJrZG93blZpZXcpO1xuXHRcdGNvbnN0IGFjdGl2ZUZpbGUgPSBhY3RpdmVWaWV3Py5maWxlO1xuXHRcdC8vIHRoaXMubG9nKGVsZW1lbnQpO1xuXHRcdGlmIChhY3RpdmVGaWxlKSB7XG5cdFx0XHQvLyB0aGlzLmxvZyhhY3RpdmVGaWxlLmJhc2VuYW1lKVxuXG5cdFx0XHRjb25zdCB0YXJnZXRMaW5rcyA9IEFycmF5LmZyb20oZWxlbWVudC5nZXRFbGVtZW50c0J5VGFnTmFtZShcImltZ1wiKSkuZmlsdGVyKFxuXHRcdFx0XHQobGluaykgPT4ge1xuXHRcdFx0XHRcdHJldHVybiBsaW5rLnNyYy5sYXN0SW5kZXhPZignOicpID09PSAzOy8vXCJhcHA6Ly8uLi4uXCJcblx0XHRcdFx0fVxuXHRcdFx0KTtcblxuXHRcdFx0bGV0IGFjdGl2ZVBhdGggPSB0aGlzLmFwcC52YXVsdC5nZXRSZXNvdXJjZVBhdGgoYWN0aXZlRmlsZSk7XG5cdFx0XHR0aGlzLmxvZyhhY3RpdmVWaWV3Py5nZXRFcGhlbWVyYWxTdGF0ZSgpKTtcblx0XHRcdHRoaXMubG9nKHRoaXMuYXBwLndvcmtzcGFjZSk7XG5cdFx0XHR0aGlzLmxvZyhhY3RpdmVQYXRoKTtcblx0XHRcdGFjdGl2ZVBhdGggPSBhY3RpdmVQYXRoID8gYWN0aXZlUGF0aC5zdWJzdHJpbmcoMCwgYWN0aXZlUGF0aC5sYXN0SW5kZXhPZihcIi9cIikpIDogJyc7XG5cblx0XHRcdGZvciAoY29uc3QgbGluayBvZiB0YXJnZXRMaW5rcykge1xuXHRcdFx0XHRsZXQgY2xlYW5MaW5rID0gbGluay5zcmMucmVwbGFjZSgnYXBwOi8vb2JzaWRpYW4ubWQvJywgJycpO1xuXHRcdFx0XHRsaW5rLnNyYyA9IGFjdGl2ZVBhdGggKyAnLycgKyBjbGVhbkxpbms7XG5cblx0XHRcdH1cblx0XHR9XG5cdH1cblxuXHR1c2VQcm9jZXNzTWFya2Rvd24oKSB7XG5cdFx0Y29uc3QgYWN0aXZlVmlldyA9IHRoaXMuYXBwLndvcmtzcGFjZS5nZXRBY3RpdmVWaWV3T2ZUeXBlKE1hcmtkb3duVmlldyk7XG5cdFx0dGhpcy5sb2coJ2FjdGl2ZVZpZXcgICcsIGFjdGl2ZVZpZXcpO1xuXHRcdGNvbnN0IGVsZW1lbnQgPSBhY3RpdmVWaWV3Py5jb250ZW50RWw7XG5cdFx0aWYgKGVsZW1lbnQpIHtcblx0XHRcdHRoaXMucHJvY2Vzc01hcmtkb3duKGVsZW1lbnQpO1xuXHRcdH1cblx0fVxuXG5cdG1vZGlmeUhUTUwoZWw6IEhUTUxFbGVtZW50LCBjdHg6IHsgc291cmNlUGF0aDogc3RyaW5nIH0pIHtcblx0XHQvLyBQZXJmb3JtIGFkZGl0aW9uYWwgbW9kaWZpY2F0aW9ucyB0byBIVE1MIGlmIG5lZWRlZFxuXHRcdHRoaXMubG9nKFwiTWFya2Rvd24gcmVuZGVyaW5nIGNvbXBsZXRlZDpcIiwgY3R4LnNvdXJjZVBhdGgpO1xuXHR9XG5cblx0Lypcblx0c2Nyb2xsIFx1NUI1MFx1NTFGRFx1NjU3MFxuXHQgKi9cblxuXHRzY3JvbGxMaW5lcyA9IGFzeW5jIChlbGVtZW50OiBFbGVtZW50KTogUHJvbWlzZTxudW1iZXI+ID0+IHtcblxuXHRcdC8vIFx1ODNCN1x1NTNENlx1NTE0M1x1N0QyMFx1NzY4NFx1OEZCOVx1NzU0Q1x1NzdFOVx1NUY2MlxuXHRcdGxldCByZWN0ID0gZWxlbWVudC5nZXRCb3VuZGluZ0NsaWVudFJlY3QoKTtcblxuXHRcdC8vIFx1ODNCN1x1NTNENlx1NTE0M1x1N0QyMFx1NzY4NFx1OUFEOFx1NUVBNlx1RkYwQ1x1NTNFRlx1ODlDMVx1OUFEOFx1NUVBNlx1RkYwQ1x1NTE4NVx1NUJCOVx1OUFEOFx1NUVBNlx1RkYwQ1x1NkVEQVx1NTJBOFx1OERERFx1NzlCQiBcdTYwM0JcdTk1N0ZcdTVFQTZcblx0XHQvLyBcdTRGN0ZcdTc1MjggY29uc3QgXHU1OEYwXHU2NjBFXHU1RTM4XHU5MUNGXHVGRjBDXHU1RTc2XHU2REZCXHU1MkEwXHU3QzdCXHU1NzhCXHU2Q0U4XHU4OUUzXG5cdFx0Y29uc3QgaGVpZ2h0OiBudW1iZXIgPSByZWN0LmhlaWdodDtcblx0XHRjb25zdCBjbGllbnRIZWlnaHQ6IG51bWJlciA9IE1hdGgucm91bmQoZWxlbWVudC5jbGllbnRIZWlnaHQpO1xuXHRcdC8vIGNvbnN0IHNjcm9sbEhlaWdodDogbnVtYmVyID0gZWxlbWVudC5zY3JvbGxIZWlnaHQ7XG5cdFx0Y29uc3Qgc2Nyb2xsVG9wOiBudW1iZXIgPSBNYXRoLnJvdW5kKGVsZW1lbnQuc2Nyb2xsVG9wKTtcblx0XHQvLyBlbGVtZW50LlxuXG5cdFx0Ly8gXHU4QkExXHU3Qjk3XHU1MTQzXHU3RDIwXHU3Njg0XHU2QkNGXHU0RTAwXHU4ODRDXHU3Njg0XHU5QUQ4XHU1RUE2XHVGRjBDXHU1MDQ3XHU4QkJFXHU2QkNGXHU0RTAwXHU4ODRDXHU3Njg0XHU5QUQ4XHU1RUE2XHU2NjJGXHU3NkY4XHU1NDBDXHU3Njg0XG5cdFx0Ly8gXHU0RjdGXHU3NTI4IGNvbnN0IFx1NThGMFx1NjYwRVx1NUUzOFx1OTFDRlx1RkYwQ1x1NUU3Nlx1NkRGQlx1NTJBMFx1N0M3Qlx1NTc4Qlx1NkNFOFx1ODlFM1xuXHRcdGNvbnN0IGxpbmVIZWlnaHQ6IG51bWJlciA9IGhlaWdodCAvIGNsaWVudEhlaWdodDtcblxuXG5cdFx0Ly8gXHU4QkExXHU3Qjk3XHU1MTQzXHU3RDIwXHU3Njg0XHU2RURBXHU1MkE4XHU4ODRDXHU2NTcwXHVGRjBDXHU0RTVGXHU1QzMxXHU2NjJGXHU2RURBXHU1MkE4XHU0RTg2XHU1OTFBXHU1QzExXHU4ODRDXG5cdFx0Ly8gXHU0RjdGXHU3NTI4IGNvbnN0IFx1NThGMFx1NjYwRVx1NUUzOFx1OTFDRlx1RkYwQ1x1NUU3Nlx1NkRGQlx1NTJBMFx1N0M3Qlx1NTc4Qlx1NkNFOFx1ODlFM1xuXHRcdGNvbnN0IHNjcm9sbExpbmVzOiBudW1iZXIgPSBNYXRoLnJvdW5kKHNjcm9sbFRvcCAvIGxpbmVIZWlnaHQpO1xuXHRcdHRoaXMubG9nKCdzY3JvbGxIZWlnaHQgJywgc2Nyb2xsVG9wICUgY2xpZW50SGVpZ2h0IC0gY2xpZW50SGVpZ2h0IC8gNCA8IDApXG5cdFx0aWYgKHNjcm9sbFRvcCAlIGNsaWVudEhlaWdodCAtIGNsaWVudEhlaWdodCAvIDQgPCAwKSB7XG5cdFx0XHR0aGlzLmxvZygnaW4gU2Nyb2xsJyk7XG5cdFx0XHR0aGlzLnVzZVByb2Nlc3NNYXJrZG93bigpXG5cdFx0fVxuXG5cblx0XHQvLyBcdTU3MjhcdTYzQTdcdTUyMzZcdTUzRjBcdTYyNTNcdTUzNzBcdTUxRkFcdTZFREFcdTUyQThcdTg4NENcdTY1NzBcblx0XHR0aGlzLmxvZygnWW91IHNjcm9sbFRvcCAnICsgc2Nyb2xsVG9wICsgJyAgLEhlaWdodCA9JyArIGNsaWVudEhlaWdodCArICcsIGNsaWVudEhlaWdodCAnICsgY2xpZW50SGVpZ2h0ICsgJyBsaW5lcy4nKTtcblx0XHRyZXR1cm4gc2Nyb2xsTGluZXM7XG5cdH07XG5cblxuXHRzY3JvbGxfdG9VcGRhdGVWaWV3KGFjdGl2ZVZpZXc6TWFya2Rvd25WaWV3KSB7XG5cdFx0bGV0IGRpdiA9IGFjdGl2ZVZpZXcuY29udGFpbmVyRWwucXVlcnlTZWxlY3RvcignLmNtLXNjcm9sbGVyJyk7XG5cdFx0dGhpcy5sb2coZGl2KVxuXHRcdC8vIEB0cy1pZ25vcmVcblx0XHR0aGlzLnJlZ2lzdGVyRG9tRXZlbnQoZGl2LCAnc2Nyb2xsJywgKGV2ZW50KSA9PiB7XG5cdFx0XHQvLyBAdHMtaWdub3JlXG5cdFx0XHR0aGlzLnNjcm9sbExpbmVzKGRpdik7XG5cdFx0XHQvLyBcdTU3MjhcdTYzQTdcdTUyMzZcdTUzRjBcdTYyNTNcdTUzNzBcdTUxRkFcdTZFREFcdTUyQThcdTc2ODRcdThERERcdTc5QkJcblx0XHRcdHRoaXMubG9nKCdFZGl0b3IgU2Nyb2xsZWQ6ICAgcGl4ZWxzIHZlcnRpY2FsbHkgYW5kIHBpeGVscyBob3Jpem9udGFsbHkuJyk7XG5cdFx0fSk7XG5cdH1cblxuXG59XG4iXSwKICAibWFwcGluZ3MiOiAiOzs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7QUFBQTtBQUFBO0FBQUE7QUFBQTtBQUFBO0FBQUEsc0JBQTREO0FBRTVELElBQXFCLHFCQUFyQixjQUFnRCx1QkFBTztBQUFBLEVBQXZEO0FBQUE7QUFDQyxTQUFRLFlBQVk7QUFDcEIsU0FBUSxNQUFNLEtBQUssWUFBWSxRQUFRLE1BQU0sTUFBTTtBQUFBLElBQ25EO0FBdUVBO0FBQUE7QUFBQTtBQUFBLHVCQUFjLE9BQU8sWUFBc0M7QUFHMUQsVUFBSSxPQUFPLFFBQVEsc0JBQXNCO0FBSXpDLFlBQU0sU0FBaUIsS0FBSztBQUM1QixZQUFNLGVBQXVCLEtBQUssTUFBTSxRQUFRLFlBQVk7QUFFNUQsWUFBTSxZQUFvQixLQUFLLE1BQU0sUUFBUSxTQUFTO0FBS3RELFlBQU0sYUFBcUIsU0FBUztBQUtwQyxZQUFNLGNBQXNCLEtBQUssTUFBTSxZQUFZLFVBQVU7QUFDN0QsV0FBSyxJQUFJLGlCQUFpQixZQUFZLGVBQWUsZUFBZSxJQUFJLENBQUM7QUFDekUsVUFBSSxZQUFZLGVBQWUsZUFBZSxJQUFJLEdBQUc7QUFDcEQsYUFBSyxJQUFJLFdBQVc7QUFDcEIsYUFBSyxtQkFBbUI7QUFBQSxNQUN6QjtBQUlBLFdBQUssSUFBSSxtQkFBbUIsWUFBWSxnQkFBZ0IsZUFBZSxvQkFBb0IsZUFBZSxT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
