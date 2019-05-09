[%bs.raw {|require('./Modal.css')|}];

[@bs.scope "document"] [@bs.val] external body: Dom.element = "body";

[@react.component]
let make = (~children) => {
  ReactDOMRe.createPortal(
    <div className="modal-container" role="dialog" ariaModal=true>
      <div className="modal-content"> children </div>
    </div>,
    body,
  );
};